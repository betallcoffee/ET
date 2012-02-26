// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.
//
#ifndef ETACCEPTOR_H
#define ETACCEPTOR_H

namespace ET
{
    class ETWatcher;
    class ETEventLoop;

    ///
    /// class for operation of listenning socket fd
    ///
    class ETAcceptor
    {
    public:
        typedef void (*newConnectCallback)(int);
        ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETAcceptor();

        int listen();

        void setNewConnectCallback(newConnectCallback cb)
        { newConnectCallback_ = cb; }

    private:
        static void handRead();

        int sockFD_;
        int listenning_;

        ETEventLoop *eventLoop_;
        ETWatcher *watcher_;

        newConnectCallback newConnectCallback_;
    }; // end class ETAcceptor
}// end namespace ET
