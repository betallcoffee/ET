//
//  Server.cpp
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Server.h"
#include "TCPServer.h"
#include "Transport.h"

using namespace ET;
using namespace HTTP;


Server::Server(EventLoop *eventLoop, const std::string &host, short port)
  : _host(host), _port(port) {
	_tcpServer = new TCPServer(eventLoop, _host.c_str(), _port);
    _tcpServer->setContext(this);
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

void Server::connectionCallback(void *ctx, Connection *conn) {
    Server *server = (Server *)ctx;
    server->connection(conn);
}

void Server::connection(Connection *conn) {
    Transport *context = new Transport(this, conn);
}
