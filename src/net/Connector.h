// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#ifndef ETCONNECTOR_H
#define ETCONNECTOR_H

#include <arpa/inet.h>

#include "Config.h"
#include "Watcher.h"

namespace ET
{
    class EventLoop;
    class HandleRequest;


    ///
    /// operator for new connector
    ///
    class Connector 
    {
    public:
        Connector(EventLoop *, const char *, short);
        ~Connector();

        void setContext(void *ctx) { ctx_ = ctx; }
        void setNewSocketCallback(NewSocketCallback callback)
        { newSocketCallback_ = callback; }

        void connect();
        void discard();

    private:
        enum connStates
        {
            kConnStatesNone,
            kConnStatesConnect,
            kConnStatesConnecting,
            kConnStatesConnected,
            kConnStatesDisconnecting,
            kConnStatesDisconnected
        };

        static void readEvent(void *);
        static void writeEvent(void *);
        static void closeEvent(void *);
        static void errorEvent(void *);

        void readHandle();
        void writeHandle();
        void closeHandle();
        void errorHandle();

        void setState(int state)
        { state_ = state; }

        void connecting(int);
        void reConnect(int);

        struct sockaddr_in serverAddr_;
        Watcher *watcher_;
        EventLoop *eventLoop_;
        void *ctx_;
        NewSocketCallback newSocketCallback_;

        int state_;
        int connect_;

    }; // end class Connector
} // end namespace ET

#endif // ETCONNECTOR_H

