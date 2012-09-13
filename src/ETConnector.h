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

#include "ETConfig.h"
#include "ETWatcher.h"

namespace ET
{
    class ETEventLoop;
    class ETHandleRequest;


    ///
    /// operator for new connector
    ///
    class ETConnector 
    {
    public:
        ETConnector(ETEventLoop *, const char *, short);
        ~ETConnector();

        void setContext(void *ctx) { ctx_ = ctx; }
        void setNewConnectionCallback(NewConnectionCallback callback)
        { newConnectionCallback_ = callback; }

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
        ETWatcher *watcher_;
        ETEventLoop *eventLoop_;
        void *ctx_;
        NewConnectionCallback newConnectionCallback_;

        int state_;
        int connect_;

    }; // end class ETConnector
} // end namespace ET

#endif // ETCONNECTOR_H

