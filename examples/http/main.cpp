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
    Logger::sharedInstance()->setLogLevel(Logger::VERBOSE);
    LogV("Log init success");
    
    KqueueSelect select;
    EventLoop eventLoop(&select);
    HTTP::Server server(&eventLoop, nullptr, 8080);
    LogV("http server init 8080");
    bool res = server.run();
    if (res) {
        LogV("http server run begin");
        while(true) {
            eventLoop.runOneLoop();
        }
        LogV("http server run end");
    } else {
        LogE("http server init error");
    }
    
    return 0;
}