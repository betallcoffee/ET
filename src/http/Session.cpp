//
//  Session.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//


#include "Connection.h"

#include "Session.h"
#include "Server.h"
#include "Request.h"
#include "ResponseRunnable.h"

using namespace ET;
using namespace HTTP;

THREAD::ThreadPool *Session::sTaskThreadPool = new THREAD::ThreadPool(10);

Session::Session(Server *server, Connection *connection) :
  _server(server), _connection(connection) {
      printf("session init\n");
     if (_connection != nullptr) {
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
     }
}

Session::~Session() {
    printf("session destroy\n");
    _requests.clear();
}

void Session::removeRequest(ET::HTTP::Request *request) {
    _requests.erase(request);
}

void Session::finishSession()
{
    printf("session finish\n");
    _connection->connectClose();
}

size_t Session::writeData(ET::BufferV &buf) {
    return _connection->send(buf);
}

void Session::readDataCallback(void *ctx, ET::Connection *conn) {
    Session *self = static_cast<Session *>(ctx);
    self->readData(conn);
}

void Session::readData(ET::Connection *conn) {
    // 1. When non request, create a new. 2. When pre request is complete parse, create a new.
    std::shared_ptr<Session> &session = _server->findSession(this);
    std::shared_ptr<Request> request = _request.lock();
    if (request == nullptr || request->status() == Request::RESPONSING) {
        request.reset(new Request(_connection));
        _requests[request.get()] = std::weak_ptr<Request>(request);
        _request = request;
    }
    
    BufferV &data = conn->readBuf();
    request->parse(data);
    
    if (request->status() == Request::PARSE_COMPLETE) {
        ResponseRunnable *responsetRunnable = new ResponseRunnable(session, request);
        Session::sTaskThreadPool->addTask(responsetRunnable);
    }
}

void Session::closeCallback(void *ctx, ET::Connection *conn) {
    Session *self = static_cast<Session *>(ctx);
    self->closeConn(conn);
}

void Session::closeConn(ET::Connection *conn) {
    printf("session close connection\n");
    _server->removeSession(this);
}

