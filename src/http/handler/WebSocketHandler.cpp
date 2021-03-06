//
//  WebSocketHandler.cpp
//  ET
//
//  Created by liang on 10/6/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#include <string>

#include "Base64.h"

#include "Connection.h"
#include "Request.h"
#include "Response.h"

#include "WebSocketHandler.hpp"

using namespace ET;
using namespace HTTP;

const char *WebSocketHandler::kGUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

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
        
        std::string secKey = request->header(RequestHeader::kSecWebSocketKey);
        secKey.append(kGUID);
        
        char sha1[41];
        memset(sha1, 0, sizeof(sha1));
        _sha1.SHA_GO(secKey.c_str(), sha1);
        
        Base64 base64;
        base64.encode(sha1);
        
        response.addHeader(ResponseHeader::kSecWebSocketAccept, base64.base64());
        
        request->connection()->lock();
        request->connection()->send(response.createHeaders());
        request->connection()->unlock();
    }
}
