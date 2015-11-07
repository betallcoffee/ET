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

#include "Request.h"
#include "Response.h"

#include "StaticFileCommand.h"

using namespace ET;
using namespace HTTP;

void ResponseRunnable::run() {
    if (_request)
    {
        // TODO 1. url 路由; 2. 链式 command 处理 request ; 3. 流式 response;
        StaticFileCommand *command = new StaticFileCommand(_request);
        command->execute();
    }
    
}
