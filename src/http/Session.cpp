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
#include "FileRunnable.h"

using namespace ET;
using namespace HTTP;

THREAD::ThreadPool *Session::sThreadPool = new THREAD::ThreadPool(10);

Session::Session(Server *server, Connection *connection) :
  _server(server), _connection(connection) {
     if (_connection != nullptr) {
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
     }
      printf("session init\n");
}

Session::~Session() {
    if (_connection) {
        delete _connection;
    }
    std::for_each(_requests.begin(), _requests.end(), [=](std::pair<Request *, Request*> pair) {
        Request *request = pair.second;
        delete request;
    });
    _requests.clear();
    printf("session destroy\n");
}

void Session::removeRequest(ET::HTTP::Request *request) {
    _requests.erase(request);
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
    if (_request == nullptr || _request->status() == Request::RESPONSEING) {
        _request = new Request(this);
        _requests[_request] = _request;
    }
    
    BufferV &data = conn->readBuf();
    _request->parse(data);
    
    if (_request->status() == Request::COMPLETE) {
        FileRunnable *fileRunnable = new FileRunnable(_request);
        Session::sThreadPool->addTask(fileRunnable);
        _request = nullptr;
    }
}

void Session::closeCallback(void *ctx, ET::Connection *conn) {
    Session *self = static_cast<Session *>(ctx);
    self->closeConn(conn);
}

void Session::closeConn(ET::Connection *conn) {
    delete this;
    _server->removeSession(this);
    printf("session close connection\n");
}

