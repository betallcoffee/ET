//
//  LoggerTarget.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_LOGGER_TARGET_
#define _ET_LOGGER_TARGET_

namespace ET
{
    
    class LoggerTarget
    {
    public:
        LoggerTarget() {};
        ~LoggerTarget() {};
        
        void output(const char *message);
        
    };
} // end ET

#endif // end _ET_LOGGER_TARGET_
