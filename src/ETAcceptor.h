// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.
//
#ifndef ETACCEPTOR_H
#define ETACCEPTOR_H

#include "ETConfig.h"
#include "ETWatcher.h"

namespace ET
{

    //
    // class for operation of listenning socket fd
    //
    
    class ETAcceptor 
    {
    public:
        ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETAcceptor();

        void setContext(void *ctx) { ctx_ = ctx; }
        void setNewConnectionCallback(NewConnectionCallback callback)
        { newConnectionCallback_ = callback; }

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

        ETWatcher watcher_;
        ETEventLoop *eventLoop_;
        void *ctx_;
        NewConnectionCallback newConnectionCallback_;

        int fd_;
        int listenning_;

    }; // end class ETAcceptor
}// end namespace ET

#endif // end ETACCEPTOR_H
