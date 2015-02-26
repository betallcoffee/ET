//
//  Transport.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Connection.h"
#include "Transport.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

Transport::Transport(Server *server, Connection *connection) :
 _server(server), _connection(connection) {
     if (_connection != nullptr) {
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
     }
}

Transport::~Transport() {
    if (_connection) {
        _connection->shutdown();
        delete _connection;
    }
}

void Transport::readDataCallback(void *ctx, ET::Connection *conn) {
    Transport *self = static_cast<Transport *>(ctx);
    self->readData(conn);
}

void Transport::readData(ET::Connection *conn) {
	BufferV &data = conn->readBuf();
	_request.parse(data);
}

void Transport::writeDataCallback(void *ctx, ET::Connection *conn) {
	Transport *self = static_cast<Transport *>(ctx);
	self->writeData(conn);
}

void Transport::writeData(ET::Connection *conn) {
}

void Transport::closeCallback(void *ctx, ET::Connection *conn) {
    Transport *self = static_cast<Transport *>(ctx);
    self->closeConn(conn);
}

void Transport::closeConn(ET::Connection *conn) {
    delete this;
}

