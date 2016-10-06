//
//  Router.cpp
//  ET
//
//  Created by liang on 9/29/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#include "StaticFileHandler.h"
#include "WebSocketHandler.hpp"

#include "Router.h"

#include "Session.h"


using namespace ET;
using namespace HTTP;


Router::Router() {
    std::string pathPattern("/?(js)?/?(\\w+)(\\.html|\\.js)");
    registerHandle(pathPattern, std::make_shared<StaticFileHandler>());
    
    std::string websocketPattern("/?chat");
    registerHandle(websocketPattern, std::make_shared<WebSocketHandler>());
}

Router::~Router() {
    
}

void Router::registerHandle(const std::string &path, std::shared_ptr<Handler> handler) {
    std::shared_ptr<std::regex> key = std::make_shared<std::regex>(path);
    _handlers[key] = handler;
}

std::shared_ptr<Handler> Router::disptach(std::shared_ptr<Session> session, std::shared_ptr<Request> request) {
    for (auto it = _handlers.begin(); it != _handlers.end(); it++) {
        auto pattern = it->first;
        std::smatch resutls;
        std::shared_ptr<Handler> handler = it->second;
        if (handler->type() & session->upgrade() && std::regex_match(request->path(), resutls, *pattern)) {
            LogD("%s match type %d, path %s", handler->name().c_str(), session->upgrade(), request->path().c_str());
            return handler->createHandler(request);
        }
    }
    LogD("default handler StaticFileHandler");
    return std::make_shared<StaticFileHandler>(request);
}
