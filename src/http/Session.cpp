//
//  Session.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//


#include "Log.h"
#include "Connection.h"

#include "Session.h"
#include "Server.h"
#include "Request.h"
#include "ResponseRunnable.h"

using namespace ET;
using namespace HTTP;

THREAD::ThreadPool* Session::sTaskThreadPool = new THREAD::ThreadPool(10);

Session::Session(Server* server, Connection* connection) :
  _server(server), _connection(connection), _isKeepLive(false) {
      LogD("Session init");
     if (_connection != nullptr) {
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
     }
}

Session::~Session() {
    LogD("Session destroy");
    _requests.clear();
}

void Session::completeResponse(std::shared_ptr<Request> request) {
    LogD("complete response : %s", request->url().c_str());
    if (_isKeepLive) {
        LogD("connection keep live");
    } else {
        LogD("connection close");
        removeRequest(request);
        finishSession();
    }
}

void Session::removeRequest(std::shared_ptr<Request> request) {
    LogD("session revmove request : %s", request->url().c_str());
    _requests.erase(request.get());
}

void Session::finishSession()
{
    LogD("Session finish");
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
    std::shared_ptr<Session> session = _server->findSession(this);
    if (_request == nullptr || _request->status() == Request::RESPONSING) {
        _request.reset(new Request(session, _connection));
        _requests[_request.get()] = _request;
    }
    
    BufferV &data = conn->readBuf();
    _request->parse(data);
    
    if (_request->status() == Request::PARSE_COMPLETE) {
        _request->setStatus(Request::RESPONSING);
        std::shared_ptr<ResponseRunnable> responsetRunnable = std::make_shared<ResponseRunnable>(_server, session, _request);
        Session::sTaskThreadPool->addTask(responsetRunnable);
    }
}

void Session::closeCallback(void *ctx, ET::Connection *conn) {
    Session *self = static_cast<Session *>(ctx);
    self->closeConn(conn);
}

void Session::closeConn(ET::Connection *conn) {
    LogD("Session close connection");
    _requests.clear();
    _server->removeSession(this);
}

