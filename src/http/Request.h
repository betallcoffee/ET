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

#include "Session.h"
#include "RequestHeader.h"
#include "Response.h"

namespace ET {
    
    class BufferV;
    class Connection;
    
namespace HTTP {
    
    class Request {
    public:
        Request(Session *session) : _session(session), _status(FIRST_LINE), _body(NULL), _response(this) {}
        Request(const std::string &url, Session *session);
        
        typedef enum Status {
        	FIRST_LINE = 1,
            PARSE_HEADER,
            READ_BODY,
            COMPLETE,
            RESPONSEING
        }eStatus;
        
        friend class Response;
        Connection &connection() { return _session->connection(); }
        
        eStatus parse(BufferV &data);
        void reset();

        eStatus status() { return _status; }
        
        const std::string &method() { return _requestHeader._method; }
        void setMethod(const std::string &method) { _requestHeader._method = method; }
        
        const std::string &url() { return _requestHeader._url; }
        void setURL(const std::string &url) { _requestHeader._url = url; } // TODO: parse path from url;
        
        const std::string &path() { return _requestHeader._path; }
        
        std::string head(const std::string &key);
        void addHead(const std::string &key, const std::string &value);
        
        Response &response() { return _response; }
        
    private:
        RequestHeader::eMethod stringToMethod(const std::string &method);
        bool parseFirstLine(BufferV &data);
        bool parseHeaders(BufferV &data);
        bool readBody(BufferV &data);
        
        Session *_session;
        eStatus _status;
        BufferV *_body;
        std::map<std::string, std::string> _headers;
        RequestHeader _requestHeader;
    
        Response _response;
    };
}
    
}

#endif // end ET_REQUEST_H
