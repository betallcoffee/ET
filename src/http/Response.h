//
//  Response.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_RESPONSE_H
#define ET_HTTP_RESPONSE_H

#include <string>

#include "BaseHeader.h"

namespace ET {
    
    class BufferV;
    class Connection;

namespace HTTP {
    
    class Request;
    
    class Response {
    public:
        Response(Request *request);
        ~Response();
        
        int statusCode() { return _statusCode; }
        const std::string &phrase() { return _phrase; }
        
    private:
        Request *_request;
        
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
