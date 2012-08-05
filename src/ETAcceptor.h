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
        typedef void (*newConnectCallback)(void *, int);
        ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETAcceptor();

        int listen();

        void setParam(void *param) 
        { param_ = param; }
        void setNewConnectCallback(newConnectCallback cb)
        { newConnectCallback_ = cb; }

    private:
        static void handRead(void *param);
        void handRead();

        int sockFD_;
        int listenning_;
        void *param_;

        ETEventLoop *eventLoop_;
        ETWatcher *watcher_;

        newConnectCallback newConnectCallback_;
    }; // end class ETAcceptor
}// end namespace ET

#endif // end ETACCEPTOR_H
