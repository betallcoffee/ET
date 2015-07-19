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


Server::Server(EventLoop *eventLoop, const char *ip, short port) : _port(port) {
    _ip = ip ? std::string(ip) : "";
    _tcpServer = new TCPServer(eventLoop, ip, _port);
    _tcpServer->setContext(this);
    _tcpServer->setConnectionCb(connectionCallback);
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
    std::for_each(_transports.begin(), _transports.end(), [=](std::pair<Transport *, Transport*> pair) {
        Transport *transport = pair.second;
        delete transport;
    });
    _transports.clear();
}

bool Server::isRunning() {
    if (_tcpServer != nullptr) {
        return _tcpServer->isRunning();
    }
    return false;
}

void Server::removeTransport(Transport *transport)
{
    _transports.erase(transport);
}

void Server::connectionCallback(void *ctx, Connection *conn) {
    Server *server = (Server *)ctx;
    server->connection(conn);
}

void Server::connection(Connection *conn) {
    Transport *transport = new Transport(this, conn);
    _transports[transport] = transport;
}
