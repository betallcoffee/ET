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
#include <map>

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
        
        std::string head(const std::string &key);
        void addHead(const std::string &key, const std::string &value);
        
    private:
        Request *_request;
        std::map<std::string, std::string> _headers;
        
        int _statusCode;
        std::string _phrase;
        
    };
}
    
}



#endif // end ET_RESPONSE_H
