//
//  Log.cpp
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <stdarg.h>

#include "Log.h"

using namespace ET;

void ET::log(Logger *logger,
         int logType,
#if defined(DEBUG)
        const char *fileName,
        int lineNo,
        const char *functionName,
#endif
        const char *format, ...)
{
    char logLineMessage[Logger::kMaxLineLength];
    
    va_list vaList;
    va_start(vaList, format);
    int length = vsnprintf(logLineMessage, Logger::kMaxLineLength, format, vaList);
    va_end(vaList);
    
#if defined(DEBUG)
    snprintf(logLineMessage + length, Logger::kMaxLineLength - length, " - %d %s", lineNo, functionName);
#endif
    
    logger->output(logType, logLineMessage);
}
