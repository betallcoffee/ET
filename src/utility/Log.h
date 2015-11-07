//
//  Log.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_LOG_
#define _ET_LOG_

#include "Logger.h"

namespace ET {
    
extern void log(Logger *logger, int logType,
#if defined(DEBUG)
    const char *fileName,
    int lineNo,
    const char *functionName,
#endif
    const char *format, ...);
    
#if defined(DEBUG)
#define LogV(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::VERBOSE, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogD(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::DBG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogW(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogE(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#else
#define LogV(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::VERBOSE, format, ##__VA_ARGS__)
#define LogD(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::DBG, format, ##__VA_ARGS__)
#define LogW(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::WARN, format, ##__VA_ARGS__)
#define LogE(format, ...) ET::log(ET::Logger::sharedInstance(), ET::Logger::ERROR, format, ##__VA_ARGS__)
#endif
    
} // end ET

#endif // end _ET_LOG_
