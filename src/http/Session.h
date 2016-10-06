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
            Session(Server* server, Connection* connection);
            ~Session();
            
            typedef enum Upgrade {
                HTTP = 0x01,
                WEBSOCKET = 0x02
            }eUpgrade;
            
            size_t writeData(BufferV &buf);
            std::shared_ptr<Connection> &connection() { return _connection; }
            
            void completeResponse(std::shared_ptr<Request> request);
            void removeRequest(std::shared_ptr<Request> request);
            void finishSession();
            
            void setKeepALive(bool b) { _isKeepALive = b; }
            
            void setUpgrade(eUpgrade upgrade) { _upgrade = upgrade; }
            eUpgrade upgrade() { return _upgrade; }
            
            static THREAD::ThreadPool* sTaskThreadPool;
            
        private:
            // Connection callback
            static void readDataCallback(void* ctx, Connection* conn);
            static void closeCallback(void* ctx, Connection* conn);
            
            void readData(Connection* conn);
            void closeConn(Connection* conn);
            
            Server* _server;
            std::shared_ptr<Connection> _connection;
            std::shared_ptr<Request> _request;
            std::map<Request*, std::shared_ptr<Request>> _requests;
            
            bool _isKeepALive;
            eUpgrade _upgrade;
        };
        
    } // end HTTP
    
} // end ET

#endif
