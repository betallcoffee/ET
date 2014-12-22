//
//  Session.h
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_SESSION_H
#define ET_HTTP_SESSION_H

#include "Router.h"
#include "Connection.h"
#include "Request.h"
#include "Response.h"

namespace ET {
    
namespace HTTP {
    
    class Server;
    
    class Session {
    public:
        Session(Server *server, Router *router, Connection *connection);
        ~Session();
        
    private:
        Server *_server;
        Router *_router;
        Connection *_connection;
        Request *_request;
        Response *_response;
        
    };
        
} // end HTTP
    
} // end ET


#endif
