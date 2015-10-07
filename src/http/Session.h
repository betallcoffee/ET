//
//  Session.h
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_SESSION_H
#define ET_HTTP_SESSION_H

#include <map>
#include "ThreadPool.h"

namespace ET {
    
    class Connection;
    class BufferV;
    
    namespace HTTP {
        
        class Server;
        class Request;
        
        class Session {
        public:
            Session(Server *server, Connection *connection);
            ~Session();
            
            size_t writeData(BufferV &buf);
            Connection &connection() { return *_connection; }
            
            void removeRequest(Request *request);
            
            
            static THREAD::ThreadPool *sThreadPool;
            
        private:
            // Connection callback
            static void readDataCallback(void *ctx, Connection *conn);
            static void closeCallback(void *ctx, Connection *conn);
            
            void readData(Connection *conn);
            void closeConn(Connection *conn);
            
            Server *_server;
            Connection *_connection;
            Request *_request;
            std::map<Request *, Request *> _requests;
        };
        
    } // end HTTP
    
} // end ET

#endif