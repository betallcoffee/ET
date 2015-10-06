//
//  Transport.h
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_SESSION_H
#define ET_HTTP_SESSION_H

namespace ET {
    
    class Connection;
    class BufferV;
    
    namespace HTTP {
        
        class Server;
        class Request;
        
        class Transport {
        public:
            Transport(Server *server, Connection *connection);
            ~Transport();
            
            size_t writeData(BufferV &buf);
            
        private:
            // Connection callback
            static void readDataCallback(void *ctx, Connection *conn);
            static void closeCallback(void *ctx, Connection *conn);
            
            void readData(Connection *conn);
            void closeConn(Connection *conn);
            
            Server *_server;
            Connection *_connection;
            Request *_request;
        };
        
    } // end HTTP
    
} // end ET

#endif
