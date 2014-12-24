//
//  Context.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Connection.h"
#include "Context.h"
#include "Request.h"
#include "Response.h"

using namespace ET;
using namespace HTTP;

Context::Context(Server *server, Router *router, Connection *connection) :
 _server(server), _router(router), _connection(connection) {
     if (_connection != nullptr) {
         _request = new Request();
         _response = new Response();
         _connection->setContext(this);
         _connection->setReadDataCallback(readDataCallback);
         _connection->setCloseCallback(closeCallback);
     }
}

Context::~Context() {
    if (_connection) {
        _connection->shutdown();
        delete _connection;
    }
    if (_request) {
        delete _request;
    }
    if (_response) {
        delete _response;
    }
}

void Context::readDataCallback(void *ctx, ET::Connection *conn, ET::BufferV *data) {
    Context *self = static_cast<Context *>(ctx);
    self->readData(conn, data);
}

void Context::readData(ET::Connection *conn, ET::BufferV *data) {
    
}

void Context::closeCallback(void *ctx, ET::Connection *conn) {
    Context *self = static_cast<Context *>(ctx);
    self->closeConn(conn);
}

void Context::closeConn(ET::Connection *conn) {
    delete this;
}

