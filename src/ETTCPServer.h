// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//

#ifndef ETTCPSERVER_H
#define ETTCPSERVER_H

#include "ETConfig.h"
#include "ETAcceptor.h"

namespace ET
{
    class ETEventLoop;
    class ETConnection;

    class ETTCPServer
    {
    public:
        ETTCPServer(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETTCPServer();

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

        static void newConnectionCallback(void *, int);
        void newConnection(int);
        void removeConnection(ETConnection *);
        void setState(int state) { state_ = state; }

        void *ctx_;
        ConnectionCb connectionCb_;

        ETEventLoop *eventLoop_;
        ETAcceptor acceptor_;

        int state_;
    }; // end class ETTCPServer
} // end namespace ET

#endif // end ETTCPSERVER_H

