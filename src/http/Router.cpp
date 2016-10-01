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
    std::string pathPattern("/?(\\w+)(\\.html)");
    registerHandle(pathPattern, std::make_shared<StaticFileHandler>());
}

Router::~Router() {
    
}

void Router::registerHandle(const std::string &path, std::shared_ptr<Handler> handler) {
    std::shared_ptr<std::regex> key = std::make_shared<std::regex>(path);
    _handlers[key] = handler;
}

std::shared_ptr<Handler> Router::disptach(std::shared_ptr<Request> request) {
    // TODO 1. 正则表达式路由;
    for (auto it = _handlers.begin(); it != _handlers.end(); it++) {
        auto pattern = it->first;
        std::smatch resutls;
        if (std::regex_match(request->path(), resutls, *pattern)) {
            LogD("match path %s", request->path().c_str());
            return it->second->createHandler(request);
        }
    }
    return std::make_shared<StaticFileHandler>(request);
}
