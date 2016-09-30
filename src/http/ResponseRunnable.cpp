//
//  ResponseRunnable.cpp
//  ET
//
//  Created by liang on 10/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <string>

#include "Connection.h"

#include "ResponseRunnable.h"

#include "Server.h"
#include "Router.h"
#include "Session.h"
#include "Request.h"
#include "Response.h"

#include "StaticFileHandler.h"

using namespace ET;
using namespace HTTP;

void ResponseRunnable::run() {
    if (_server && _session && _request)
    {
        // TODO 1. rewrite 处理 request; 2. 流式 response;
        std::shared_ptr<Handler> handler = _server->getRouter()->disptach(_request);
        handler->execute();
        
        // TODO support keep live.
        _session->removeRequest(_request.get());
        _session->finishSession();
    }
    
}
