//
//  Transport.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//


#include "Connection.h"
#include "Transport.h"
#include "Server.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

THREAD::ThreadPool *Transport::sThreadPool = new THREAD::ThreadPool(10);

Transport::Transport(Server *server, Connection *connection) :
 _server(server), _connection(connection) {
     if (_connection != nullptr) {
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
         _request = new Request(this);
     }
}

Transport::~Transport() {
    if (_connection) {
        delete _connection;
    }
}

size_t Transport::writeData(ET::BufferV &buf) {
    return _connection->send(buf);
}

void Transport::readDataCallback(void *ctx, ET::Connection *conn) {
    Transport *self = static_cast<Transport *>(ctx);
    self->readData(conn);
}

void Transport::readData(ET::Connection *conn) {
	BufferV &data = conn->readBuf();
    _request->parse(data);
}

void Transport::closeCallback(void *ctx, ET::Connection *conn) {
    Transport *self = static_cast<Transport *>(ctx);
    self->closeConn(conn);
}

void Transport::closeConn(ET::Connection *conn) {
    delete this;
    _server->removeTransport(this);
}

