//
//  main.cpp
//  ETTime
//
//  Created by liang on 10/14/14.
//  Copyright (c) 2014 Tina. All rights reserved.
//

#include "TimeServer.h"

// ET lib headers
#include "ET.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    KqueueSelect select;
    EventLoop eventLoop(&select);
    TimeServer timeServer(&eventLoop, NULL, 8080);
    printf("time server init 8080\n");
    printf("time server run begin\n");
    if (timeServer.run()){
        printf("time server run end\n");
    } else {
        printf("time server init error\n");
    }

    return 0;
}
