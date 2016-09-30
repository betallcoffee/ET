//
//  Router.cpp
//  ET
//
//  Created by liang on 9/29/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#include "Router.h"

#include "StaticFileHandler.h"

using namespace ET;
using namespace HTTP;


Router::Router() {
}

Router::~Router() {
    
}

void Router::registerHandle(std::shared_ptr<const std::string> path, std::shared_ptr<Handler> handler) {
    _handlers[path] = handler;
}

std::shared_ptr<Handler> Router::disptach(std::shared_ptr<Request> request) {
    // TODO 1. 正则表达式路由;
    return std::make_shared<StaticFileHandler>(request);
}
