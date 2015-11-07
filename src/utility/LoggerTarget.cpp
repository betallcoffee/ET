//
//  LoggerTarget.cpp
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <stdio.h>

#include "LoggerTarget.h"

using namespace ET;

void LoggerTarget::output(const char *message)
{
    printf("%s\n", message);
}
