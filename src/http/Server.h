//
//  Server.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_SERVER_H
#define ET_HTTP_SERVER_H

#include <string>
#include <map>
#include "Request.h"
#include "Response.h"

namespace ET {
    
namespace HTTP {
    typedef void (*ServeHandle)(Reqeust *req, Response *res);
    
    class Server {
    public:
        Server(const std::string *host, short port);
        ~Server();
        
        bool run();
        void stop();
        int isRunning() { return state_ == kServerStatesRunning; }
        
        void setContext(void *ctx) { ctx_ = ctx; }
        void setConnectionCb(ConnectionCb connectionCb)
        { connectionCb_ = connectionCb; }
        
        void handle(const std::string *path, ServeHandle handle);
        
    private:
        enum serverStates
        {
            kServerStatesNone,
            kServerStatesRunning,
            kServerStatesStopped
        };
        
        static void newConnectionCallback(void *, int);
        void defaultConnection(Connection *);
        void newConnection(int);
        void removeConnection(Connection *) {}
        void setState(int state) { state_ = state; }
        
        EventLoop *eventLoop_;
        Acceptor acceptor_;
        
        int state_;
        void *ctx_;
        ConnectionCb connectionCb_;
        
        std::string _host;
        short _port;
        std::map<std::string, ServeHandle> _router;
        
    };
} // end namespace HTTP
    
} // end namespace ET


#endif // end ET_HTTP_SERVER_H
