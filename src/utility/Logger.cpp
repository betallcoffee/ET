//
//  Logger.cpp
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "Logger.h"
#include "Timestamp.h"
#include "LoggerTarget.h"

using namespace ET;

static Logger *gSharedInstance;

// must call it when startup.
Logger *Logger::sharedInstance()
{
    if (gSharedInstance == nullptr)
    {
        gSharedInstance = new Logger();
        auto loggerTarget = std::make_shared<LoggerTarget>(*(new LoggerTarget()));
        gSharedInstance->addLoggerTarget(loggerTarget);
    }
    
    return gSharedInstance;
}

void Logger::output(int logType, const char *message)
{
    if (logType < _logLevel)
    {
        return;
    }
    
    char logLineMessage[kMaxLineLength];
    std::string timestamp = Timestamp::now().toFormattedString();
    snprintf(logLineMessage, kMaxLineLength, "%s [%s] %s", timestamp.c_str(), getMaskString(logType), message);
    
    std::for_each(_targetList.begin(), _targetList.end(), [=](std::shared_ptr<LoggerTarget> loggerTarget) {
        loggerTarget->output(logLineMessage);
    });
}

const char *Logger::getMaskString(int logType)
{
    switch (logType)
    {
        case VERBOSE:
            return "VERBOSE";
            break;
        case DBG:
            return "DEBUG";
            break;
        case WARN:
            return "WARN";
            break;
        case ERROR:
            return "ERROR";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

