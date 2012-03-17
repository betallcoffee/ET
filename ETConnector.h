// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#ifndef ETCONNECTOR_H
#define ETCONNECTOR_H

namespace ET
{
    class ETEventLoop;
    class ETWatcher;

enum connStates
{
    connStatesConnected,
    connStatesConnecting,
    connStatesDisconnected,
    connStatesDisconnecting
};

    ///
    /// operator for new connector
    ///
    class ETConnector
    {
    public:
        typedef void (*callback)(ETConnector *);
        typedef void (*readCallback)(ETConnector *, char *, int lenght);

        ETConnector(ETEventLoop *eventLoop, int sockFD);
        ~ETConnector();

        void connectEstablished();
        void connectDestroy();

        void setState(int state)
        { state_ = state; }
        void setWriteCompleteCallback(callback cb)
        { writeCompleteCallback_ = cb; }
        void setReadCallback(readCallback cb)
        { readCallback_ = cb; }
        void setConnectCallback(callback cb)
        { connectCallback_ = cb; }

        void send(char *data, int length);

    private:
        static void handWrite(void *param);
        static void handRead(void *param);
        static void handError(void *param);
        static void handClose(void *param);
        
        void handWrite();
        void handRead();
        void handError();
        void handClose();

        ETEventLoop *eventLoop_;
        ETWatcher *watcher_;
        int state_;
        char *writeData_;
        int writeLength_;
        int writeIndex_;
        char *readData_;
        int readLength_;

        callback writeCompleteCallback_;
        callback connectCallback_;
        readCallback readCallback_;
    }; // end class ETConnector
} // end namespace ET

#endif // ETCONNECTOR_H

