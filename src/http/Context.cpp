//
//  Context.cpp
//  ET
//
//  Created by liang on 12/24/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include "Connection.h"
#include "Context.h"

using namespace ET;
using namespace HTTP;

Context::Context(Server *server, Router *router, Connection *connection) {
    _server = server;
    _router = router;
    _connection = connection;
}

Context::~Context() {
    if (_connection) {
        _connection->shutdown();
        delete _connection;
    }
}

void Context::go() {
    
}

