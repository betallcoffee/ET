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

namespace ET {
    
    class TCPServer;
    class EventLoop;
    class Connection;
    
    
namespace HTTP {

    class Session;
    /**
     * @brief 初始化网络，与路由表
     */
    // TODO 配置文件加载
    class Server {
    public:
        Server(EventLoop *eventLoop, const char *ip, short port);
        ~Server();
        
        bool run();
        void stop();
        bool isRunning();
        
        std::shared_ptr<Session> &findSession(Session *session);
        void removeSession(Session *session);
        
    private:
        
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);
        
        TCPServer *_tcpServer;
        std::string _ip;
        short _port;
        std::map<Session *, std::shared_ptr<Session>> _sessions;
    };
} // end namespace HTTP
    
} // end namespace ET


#endif // end ET_HTTP_SERVER_H
