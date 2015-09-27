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
    KqueueSelect select;
    EventLoop eventLoop(&select);
    HTTP::Server server(&eventLoop, nullptr, 8080);
    printf("http server init 8080\n");
    bool res = server.run();
    if (res) {
        printf("http server run begin\n");
        while(true) {
            eventLoop.runOneLoop();
        }
        printf("http server run end\n");
    } else {
        printf("http server init error\n");
    }
    
    return 0;
}