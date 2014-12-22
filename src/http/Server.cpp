//
//  Server.cpp
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "KqueueSelect.h"
#include "Server.h"

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

void Server::destroy(ET::HTTP::Session *session) {
    if (session != nullptr) {
        char pointer[20];
        sprintf(pointer, "%p", session);
        std::string key(pointer);
        if (_sessions[key] != nullptr) {
            _sessions.erase(key);
            delete session;
        }

    }
}

void Server::newConnectionCallback(void *ctx, int fd) {
    Server *server = (Server *)ctx;
    server->newConnection(fd);
}

void Server::newConnection(int fd) {
    Connection *conn = new Connection(_eventLoop, fd);
    Session *session = new Session(this, _router, conn);
    char pointer[20];
    sprintf(pointer, "%p", session);
    std::string key(pointer);
    _sessions[key] = session;
}
