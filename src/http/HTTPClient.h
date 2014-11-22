//
//  HTTPClient.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_CLIENT_H
#define ET_HTTP_CLIENT_H

#include <map>
#include <string>
#include "Request.h"
#include "Response.h"
#include "BufferV.h"
#include "Connector.h"
#include "Connection.h"

namespace ET {
    
    namespace HTTP {
        typedef void (*ClientHandle)(Response *res);
        
        class HTTPClient {
        public:
            HTTPClient();
            ~HTTPClient();
            
            void send(Request *req, BufferV *body);
            
        private:
            EventLoop *eventLoop_;
            std::map<std::string, Connector *> _connectors;
            std::map<std::string, Connection *> _connections;
        };
    }
    
}

#endif // end ET_HTTP_CLIENT_H
