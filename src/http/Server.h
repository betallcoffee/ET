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

    /**
     * @brief 初始化网络，与路由表
     */
    // TODO 配置文件加载
    class Server {
    public:
        Server(EventLoop *eventLoop, const std::string &host, short port);
        ~Server();
        
        bool run();
        void stop();
        bool isRunning();
        
    private:
        
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);
        
        TCPServer *_tcpServer;
        std::string _host;
        short _port;
    };
} // end namespace HTTP
    
} // end namespace ET


#endif // end ET_HTTP_SERVER_H
