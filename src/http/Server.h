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

#include "Router.h"

namespace ET {
    
    class EventLoop;
    class Acceptor;
    
namespace HTTP {

    /**
     * @brief 初始化网络，与路由表
     */
    // TODO 配置文件加载
    class Server {
    public:
        Server(const std::string &host, short port);
        ~Server();
        
        bool run();
        void stop();
        int isRunning() { return _status == RUNNING; }
        
        void registerHandle(const std::string *path, Handle handle);
        
    private:
        typedef enum eStatus
        {
            NONE,
            RUNNING,
            STOPPED
        }eStatus;
        
        static void newConnectionCallback(void *ctx, int fd);
        void newConnection(int fd);
        
        void setStatus(eStatus status) { _status = status; }
        
        EventLoop *_eventLoop;
        Acceptor *_acceptor;
        
        eStatus _status;
        
        std::string _host;
        short _port;
        
        Router *_router;
        
    };
} // end namespace HTTP
    
} // end namespace ET


#endif // end ET_HTTP_SERVER_H
