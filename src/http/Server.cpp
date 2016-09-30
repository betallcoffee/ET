//
//  Server.cpp
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Server.h"
#include "TCPServer.h"
#include "Session.h"

using namespace ET;
using namespace HTTP;


Server::Server(EventLoop *eventLoop, const char *ip, short port) : _port(port) {
    _ip = ip ? std::string(ip) : "";
    _tcpServer = new TCPServer(eventLoop, ip, _port);
    _tcpServer->setContext(this);
    _tcpServer->setConnectionCb(connectionCallback);
    
    _router = std::make_shared<Router>();
}

Server::~Server() {
    if (_tcpServer != nullptr) {
        delete _tcpServer;
    }
}

bool Server::run() {
    if (_tcpServer != nullptr) {
        return _tcpServer->run();
    }
    return false;
}

void Server::stop() {
    _sessions.clear();
}

bool Server::isRunning() {
    if (_tcpServer != nullptr) {
        return _tcpServer->isRunning();
    }
    return false;
}

std::shared_ptr<Session> &Server::findSession(Session *session) {
    return _sessions[session];
}

void Server::removeSession(Session *session)
{
    _sessions.erase(session);
}

void Server::connectionCallback(void *ctx, Connection *conn) {
    Server *server = (Server *)ctx;
    server->connection(conn);
}

void Server::connection(Connection *conn) {
    std::shared_ptr<Session> session(new Session(this, conn));
    _sessions[session.get()] = session;
}
