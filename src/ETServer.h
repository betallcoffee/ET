// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.

#ifndef ETSERVER_H
#define ETSERVER_H

#include <map>

namespace ET
{
    class ETEventLoop;
    class ETAcceptor;
    class ETConnector;

enum serverStates
{
    serverStatesRunning,
    serverStatesStopped
};

    ///
    /// operator for a TCP server
    ///
    class ETServer
    {
    public:
        typedef void (*callback)(ETConnector *);
        typedef void (*readCallback)(ETConnector *, char *, int lenght);

        ETServer(char *ip, unsigned short port);
        ~ETServer();

        void start();

        void setWriteCompleteCallback(callback cb)
        { writeCompleteCallback_ = cb; }
        void setReadCallback(readCallback cb)
        { readCallback_ = cb; }
        void setConnectCallback(callback cb)
        { connectCallback_ = cb; }

    private:
        static void newConnector(void *param, int fd);
        void newConnector(int fd);

        ETEventLoop *eventLoop_;
        ETAcceptor *acceptor_;
        std::map<int, ETConnector*> connectorList_;

        int state_;
        callback writeCompleteCallback_;
        readCallback readCallback_;
        callback connectCallback_;
    }; // end class ETServer
} // end namespace ET
#endif // ETSERVER_H
