//
//  Logger.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_LOGGER_
#define _ET_LOGGER_

#include <vector>

namespace ET {
    
    class LoggerTarget;
    
    class Logger {
    public:
        Logger() {};
        ~Logger() {};
        
        // must call it when startup.
        static Logger *sharedInstance();
        virtual void output(int logType, const char *message);
        
        void setLogLevel(int logLevel) { _logLevel = logLevel; }
        void addLoggerTarget(std::shared_ptr<LoggerTarget> &loggerTarget) { _targetList.push_back(loggerTarget); };
        
        typedef enum {
            NONE    = 0x00,
            VERBOSE = 0x01,
            DBG     = 0x02,
            WARN    = 0X04,
            ERROR   = 0x08
        }eLogType;
        static const int kMaxLineLength = 512;
        
    private:
        const char *getMaskString(int logType);
        
        int _logLevel;
        std::vector<std::shared_ptr<LoggerTarget>> _targetList;
        
    };
    
} // end ET

#endif // end _ET_LOGGER_
