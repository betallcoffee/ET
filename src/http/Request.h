//
//  Request.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_REQUEST_H
#define ET_HTTP_REQUEST_H

#include <string>
#include "BaseMessage.h"

namespace ET {
    
    class BufferV;
    
namespace HTTP {
    
    class Request : public BaseMessage {
    public:
        Request() {}
        Request(const std::string &url);
        int parse(BufferV &buf);
        
        typedef enum eMethod {
            GET = 1,
            HEAD,
            POST,
            PUT,
            TRACE,
            OPTIONS,
            DELETE
        }eMethod;
        
        typedef enum eStatus {
            PARSEHEAD = 1,
            READBODY = 2,
            COMPLETE = 3
        }eStatus;
        
        const std::string *method() { return &_method; }
        eStatus status() { return _status; }
        void setMethod(const std::string *method) { _method = *method; }
        const std::string *url() { return &_url; }
        void setURL(const std::string *url) { _url = *url; } // TODO: parse path from url;
        const std::string *path() { return &_path; }
        
    private:
        eMethod _m;
        eStatus _status;
        std::string _method;
        std::string _url;
        std::string _path;
        BufferV *_body;
        
        std::string _clientIP;
        std::string _from;
        std::string _host;
        std::string _referer;
        std::string _userAgent;
        
        std::string _accept;
        std::string _acceptCharset;
        std::string _acceptEncoding;
        std::string _acceptLanguage;
        
        std::string _expect;
        std::string _ifMatch;
        std::string _ifModifiedSince;
        std::string _ifNoneMatch;
        std::string _ifRange;
        std::string _ifUnmodifiedSince;
        std::string _range;
        
        std::string _authorization;
        std::string _cookies;
        std::string _cookies2;
    };
}
    
}

#endif // end ET_REQUEST_H
