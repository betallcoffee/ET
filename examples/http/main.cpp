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
    LogD("Log init success");
    
    KqueueSelect select;
    EventLoop eventLoop(&select);
    HTTP::Server server(&eventLoop, nullptr, 8080);
    LogD("http server init 8080");
    LogD("http server run begin");
    if (server.run()) {
        LogD("http server run end");
    } else {
        LogE("http server init error");
    }
    
    return 0;
}