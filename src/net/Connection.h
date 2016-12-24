// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//

#ifndef ETCONNECTION_H
#define ETCONNECTION_H

#include "Net.h"
#include "../utility/BufferV.h"

namespace ET
{
    class EventLoop;
    class Watcher;

    //
    // TCP connection, for both client and server usage.
    //
    
    class Connection
    {
    public:
        Connection(EventLoop *eventLoop, int fd);
        ~Connection();

        int isConnected() { return state_ == kConnStatesConnected; }

        void setArg(void *arg) { arg_ = arg; }
        void *getArg() { return arg_; }
        void setContext(void *ctx) { ctx_ = ctx; }
        void setConnectCallback(ConnectCallback connectCallback)
        { connectCallback_ = connectCallback; }
        void setReadDataCallback(ReadDataCallback readDataCallback)
        { readDataCallback_ = readDataCallback; }
        void setWriteCompleteCallback(WriteCompleteCallback writeCompleteCallback)
        { writeCompleteCallback_ = writeCompleteCallback; }
        void setCloseCallback(CloseCallback closeCallback)
        { closeCallback_ = closeCallback; }

        size_t send(const char *, size_t);
        size_t send(BufferV &);
        BufferV &readBuf() { return inBuf_; }

        void lock();
        void unlock();
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

        void defaultReadData();

        Watcher *watcher_;
        EventLoop *eventLoop_;
        
        int state_;
        BufferV inBuf_;
        BufferV outBuf_;

        void *arg_;
        void *ctx_;
        ReadDataCallback readDataCallback_;
        WriteCompleteCallback writeCompleteCallback_;
        CloseCallback closeCallback_;
        ConnectCallback connectCallback_;

    }; // end class Connection
} // end namespace ET

#endif // ETCONNECTION_H

