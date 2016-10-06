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

#include "BufferV.h"

#include "ResponseHeader.h"

namespace ET {
    
    class BufferV;
    class Connection;

namespace HTTP {
    
    class Request;
    
    class Response {
    public:
        Response(Request *request);
        ~Response();
        
        typedef enum StatusCode {
            SWITCH = 101,
            OK = 200,
            NOTFOUND = 404
        }eStatusCode;
        
        static const std::string kCRLF;
        static const std::string kSep;
        
        int statusCode() { return _statusCode; }
        void setStatusCode(int statusCode) { _statusCode = statusCode; }
        
        const std::string &phrase() { return _phrase; }
        void setPhrase(const std::string &phrase) { _phrase = phrase; }
        
        std::string header(const std::string &key);
        void addHeader(const std::string &key, const std::string &value);
        BufferV &createHeaders();
        
    private:
        void prepareHeaders();
        
        Request *_request;
        std::map<std::string, std::string> _headers;
        
        int _statusCode;
        std::string _phrase;
        
        BufferV _buf;
    };
}
    
}



#endif // end ET_RESPONSE_H
