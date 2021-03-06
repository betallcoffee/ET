//
//  main.cpp
//  EThttp
//
//  Created by liang on 7/19/15.
//  Copyright (c) 2015 tina. All rights reserved.
//

// ET lib headers
#include "ET.h"

using namespace ET;

int main()
{
    // init log
    Logger::sharedInstance();
    Logger::sharedInstance()->setLogLevel(Logger::NONE);
    Log("Log init success");
    Base64 base64;
    base64.encode("hello world");
    Log("%s base64: %s", base64.plain(), base64.base64());
    base64.decode(base64.base64());
    Log("%s plain: %s", base64.base64(), base64.plain());
    
    KqueueSelect select;
    EventLoop eventLoop(&select);
    HTTP::Server server(&eventLoop, nullptr, 8080);
    Log("http server init 8080");
    Log("http server run begin");
    if (server.run()) {
        Log("http server run end");
    } else {
        Log("http server run error");
    }
    
    return 0;
}
