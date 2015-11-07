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

#include "Response.h"
#include "Session.h"
#include "RequestHeader.h"

namespace ET {
    
    class BufferV;
    class Connection;
    
namespace HTTP {
    
    class Request {
    public:
        Request(std::shared_ptr<Connection> &connection) : _connection(connection), _status(FIRST_LINE), _body(NULL), _response(this) {
            printf("request init\n");
        }

        ~Request() { printf("request destory\n"); }
        
        typedef enum Status {
        	FIRST_LINE = 1,
            PARSE_HEADER,
            READ_BODY,
            PARSE_COMPLETE,
            RESPONSING
        }eStatus;
        
        friend class Response;
        std::shared_ptr<Connection> &connection() { return _connection; }
        
        eStatus parse(BufferV &data);
        void reset();

        void responsing();
        eStatus status() { return _status; }
        
        const std::string &method() { return _requestHeader._method; }
        void setMethod(const std::string &method) { _requestHeader._method = method; }
        
        const std::string &url() { return _requestHeader._url; }
        void setURL(const std::string &url) { _requestHeader._url = url; } // TODO: parse path from url;
        
        const std::string &path() { return _requestHeader._path; }
        
        std::string header(const std::string &key);
        void addHeader(const std::string &key, const std::string &value);
        
        Response &response() { return _response; }
        
    private:
        RequestHeader::eMethod stringToMethod(const std::string &method);
        bool parseFirstLine(BufferV &data);
        bool parseHeaders(BufferV &data);
        bool readBody(BufferV &data);
        
        std::shared_ptr<Connection> _connection;
        eStatus _status;
        BufferV *_body;
        std::map<std::string, std::string> _headers;
        RequestHeader _requestHeader;
    
        Response _response;
    };
}
    
}

#endif // end ET_REQUEST_H
