//
//  Server.cpp
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "KqueueSelect.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"

#include "Server.h"

#include "Request.h"
#include "Response.h"
#include "Context.h"

using namespace ET;
using namespace ET::HTTP;


Server::Server(const std::string &host, short port) : _host(host), _port(port) {
    _eventLoop = new EventLoop(new KqueueSelect());
    _acceptor = new Acceptor(_eventLoop, _host.c_str(), _port);
    _acceptor->setContext(this);
    _acceptor->setNewConnectionCallback(newConnectionCallback);
    _router = new Router();
    _status = NONE;
}

Server::~Server() {
    if (_acceptor != nullptr) {
        delete _acceptor;
    }
    if (_eventLoop != nullptr) {
        delete  _eventLoop;
    }
}

bool Server::run() {
    int ret = _acceptor->listen();
    if (ret == 0) {
        _status = RUNNING;
        return true;
    }
    return false;
}

void Server::stop() {
    _status = STOPPED;
}

void Server::registerHandle(const std::string *path, Handle handle) {
    _router->registerHandle(path, handle);
}

void Server::newConnectionCallback(void *ctx, int fd) {
    Server *server = (Server *)ctx;
    server->newConnection(fd);
}

void Server::newConnection(int fd) {
    Connection *conn = new Connection(_eventLoop, fd);
    Context *context = new Context(this, _router, conn);
    context->go();
}
