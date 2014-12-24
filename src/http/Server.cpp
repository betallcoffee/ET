//
//  Server.cpp
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Server.h"

#include "TCPServer.h"

#include "Request.h"
#include "Response.h"
#include "Context.h"

using namespace ET;
using namespace HTTP;


Server::Server(EventLoop *eventLoop, const std::string &host, short port)
  : _host(host), _port(port), _tcpServer(new TCPServer(eventLoop, host.c_str(), port)) {
    _tcpServer->setContext(this);
    _router = new Router();
}

Server::~Server() {
    if (_tcpServer != nullptr) {
        delete _tcpServer;
    }
}

bool Server::run() {
    if (_tcpServer != nullptr) {
        return _tcpServer->run() == 0;
    }
    return false;
}

void Server::stop() {
}

bool Server::isRunning() {
    if (_tcpServer != nullptr) {
        return _tcpServer->isRunning();
    }
    return false;
}

void Server::registerHandle(const std::string *path, Handle handle) {
    _router->registerHandle(path, handle);
}

void Server::connectionCallback(void *ctx, Connection *conn) {
    Server *server = (Server *)ctx;
    server->connection(conn);
}

void Server::connection(Connection *conn) {
    Context *context = new Context(this, _router, conn);
}
