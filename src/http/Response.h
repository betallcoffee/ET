//
//  Response.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_RESPONSE_H
#define ET_RESPONSE_H

#include <string>
#include "BaseMessage.h"
#include "BufferV.h"

namespace ET {

namespace HTTP {
    class Response : public BaseMessage {
    public:
        int parse(BufferV *buf);
        int statusCode() { return _statusCode; }
        const std::string *phrase() { return *_phrase; }
        
    private:
        int _statusCode;
        std::string _phrase;
        
        std::string _age;
        std::string _public;
        std::string _retryAfter;
        std::string _server;
        std::string _title;
        std::string _warning;
        
        std::string _accpetRanges;
        
        std::string _setCookies;
        std::string _setCookies2;
        std::string _WWWAuthenticate;
    };
}
    
}



#endif // end ET_RESPONSE_H
