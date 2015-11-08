// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//

#ifndef ETTCPSERVER_H
#define ETTCPSERVER_H

#include "Net.h"
#include "Acceptor.h"

namespace ET
{
    class EventLoop;
    class Connection;

    class TCPServer
    {
    public:
        TCPServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~TCPServer();

        int run();
        int isRunning() { return state_ == kServerStatesRunning; }

        void setContext(void *ctx) { ctx_ = ctx; }
        void setConnectionCb(ConnectionCb connectionCb)
        { connectionCb_ = connectionCb; }

    private:
        enum serverStates
        {
            kServerStatesNone,
            kServerStatesRunning,
            kServerStatesStopped
        };

        static void newSocketCallback(void *, int);
        void newConnection(int);
        void removeConnection(Connection *) {}
        void setState(int state) { state_ = state; }

        EventLoop *eventLoop_;
        Acceptor acceptor_;

        int state_;
        void *ctx_;
        ConnectionCb connectionCb_;
    }; // end class TCPServer
} // end namespace ET

#endif // end ETTCPSERVER_H

