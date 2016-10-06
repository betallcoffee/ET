//
//  WebSocketHandler.cpp
//  ET
//
//  Created by liang on 10/6/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#include <string>

#include "File.h"
#include "BufferV.h"
#include "StringUtility.h"

#include "Connection.h"
#include "Request.h"
#include "Response.h"
#include "ResponseRunnable.h"

#include "WebSocketHandler.hpp"



using namespace ET;
using namespace HTTP;
using namespace STRING;

WebSocketHandler::WebSocketHandler(std::shared_ptr<Request> request) {
    _request = request;
}
WebSocketHandler::~WebSocketHandler() {}

std::shared_ptr<Handler> WebSocketHandler::createHandler(std::shared_ptr<Request> request) {
    return std::make_shared<WebSocketHandler>(request);
}

void WebSocketHandler::execute() {
    std::shared_ptr<Request> request = _request.lock();
    if (request) {
        Response &response = request->response();
        response.setStatusCode(Response::SWITCH);
        response.setPhrase("Switching Protocols");
        
        request->connection()->send(response.createHeaders());
    }
}
