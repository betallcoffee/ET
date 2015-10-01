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
#include <map>
#include "RequestHeader.h"
#include "ThreadPool.h"

namespace ET {
    
    class BufferV;
    class Response;
    
namespace HTTP {
    
    class Request {
    public:
        Request() : _status(FIRST_LINE), _body(NULL) {}
        Request(const std::string &url);
        
        typedef enum Status {
        	FIRST_LINE = 1,
            PARSE_HEADER,
            READ_BODY,
            COMPLETE
        }eStatus;
        
        eStatus parse(BufferV &data);
        void reset();

        const std::string &method() { return _requestHeader._method; }
        eStatus status() { return _status; }
        void setMethod(const std::string &method) { _requestHeader._method = method; }
        const std::string &url() { return _requestHeader._url; }
        void setURL(const std::string &url) { _requestHeader._url = url; } // TODO: parse path from url;
        const std::string &path() { return _requestHeader._path; }
        
    private:
        RequestHeader::eMethod stringToMethod(const std::string &method);
        bool parseFirstLine(BufferV &data);
        bool parseHeaders(BufferV &data);
        bool readBody(BufferV &data);
        
        static THREAD::ThreadPool *sThreadPool;

        eStatus _status;
        BufferV *_body;
        std::map<std::string, std::string> _headers;
        RequestHeader _requestHeader;
    
        Response *_response;
        
    };
}
    
}

#endif // end ET_REQUEST_H
