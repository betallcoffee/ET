// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//

#ifndef ETCONNECTION_H
#define ETCONNECTION_H

#include "ETConfig.h"
#include "ETBufferV.h"

namespace ET
{
    class ETEventLoop;
    class ETWatcher;

    //
    // TCP connection, for both client and server usage.
    //
    
    class ETConnection
    {
    public:
        ETConnection(ETEventLoop *eventLoop, int fd);
        ~ETConnection();

        int isConnected() { return state_ == kConnStatesConnected; }

        void setArg(void *arg) { arg_ = arg; }
        void *getArg() { return arg_; }
        void setContext(void *ctx) { ctx_ = ctx; }
        void setConnectCallback(ConnectCallback connectCallback)
        { connectCallback_ = connectCallback; }
        void setMessageCallback(MessageCallback messageCallback)
        { messageCallback_ = messageCallback; }
        void setWriteCompleteCallback(WriteCompleteCallback writeCompleteCallback)
        { writeCompleteCallback_ = writeCompleteCallback; }
        void setCloseCallback(CloseCallback closeCallback)
        { closeCallback_ = closeCallback; }

        int send(const char *, int);
        int send(ETBufferV *);

        void connectEstablish();
        void connectClose();
        void shutdown();
        
    private:
        enum connStates
        {
            kConnStatesNone,
            kConnStatesConnected,
            kConnStatesDisconnecting,
            kConnStatesDisconnected
        };
        static const int kBufInitSize = 128;

        static void readEvent(void *);
        static void writeEvent(void *);
        static void closeEvent(void *);
        static void errorEvent(void *);

        void readHandle();
        void writeHandle();
        void closeHandle();
        void errorHandle();

        void setState(int state) { state_ = state; }
        void shutdownWrite();

        void defaultMessage(ETBufferV *msg);

        ETWatcher *watcher_;
        ETEventLoop *eventLoop_;
        
        int state_;
        ETBufferV inBuf_;
        ETBufferV outBuf_;

        void *arg_;
        void *ctx_;
        MessageCallback messageCallback_;
        WriteCompleteCallback writeCompleteCallback_;
        CloseCallback closeCallback_;
        ConnectCallback connectCallback_;

    }; // end class ETConnection
} // end namespace ET

#endif // ETCONNECTION_H

