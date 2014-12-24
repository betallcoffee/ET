//
//  Context.h
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_SESSION_H
#define ET_HTTP_SESSION_H

namespace ET {
    
    class Connection;
    
namespace HTTP {
    
    class Server;
    class Router;
    class Request;
    class Response;
    
    class Context {
    public:
        Context(Server *server, Router *router, Connection *connection);
        Context();
        
        void go();
        
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
