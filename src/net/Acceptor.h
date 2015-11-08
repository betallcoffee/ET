// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.
//
#ifndef ETACCEPTOR_H
#define ETACCEPTOR_H

#include "Net.h"

namespace ET
{
    class EventLoop;
    class Watcher;

    //
    // class for operation of listenning socket fd
    //
    
    class Acceptor
    {
    public:
        Acceptor(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~Acceptor();

        void setContext(void *ctx) { ctx_ = ctx; }
        void setNewSocketCallback(NewSocketCallback callback)
        { newSocketCallback_ = callback; }

        // the server begin to listen ip:port, and running.
        int listen();

    private:
        static void readEvent(void *);
        static void writeEvent(void *);
        static void closeEvent(void *);
        static void errorEvent(void *);

        void readHandle();
        void writeHandle();
        void closeHandle();
        void errorHandle();

        Watcher *watcher_;
        EventLoop *eventLoop_;
        void *ctx_;
        NewSocketCallback newSocketCallback_;

        int fd_;
        int listenning_;

    }; // end class Acceptor
}// end namespace ET

#endif // end ETACCEPTOR_H
