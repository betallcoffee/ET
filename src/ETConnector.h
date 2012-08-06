// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#ifndef ETCONNECTOR_H
#define ETCONNECTOR_H

#include "ETConfig.h"
#include "ETWatcher.h"

namespace ET
{
    class ETEventLoop;
    class ETAcceptor;
    class ETHandleRequest;

enum connStates
{
    kConnStatesNone,
    kConnStatesConnecting,
    kConnStatesConnected,
    kConnStatesDisconnecting,
    kConnStatesDisconnected
};

    ///
    /// operator for new connector
    ///
    class ETConnector 
    {
    public:
        ETConnector(ETEventLoop *eventLoop, ETAcceptor *acceptor);
        ~ETConnector();

        static void readEvent(void *);
        static void writeEvent(void *);
        static void closeEvent(void *);
        static void errorEvent(void *);

        void readHandle();
        void writeHandle();
        void closeHandle();
        void errorHandle();

        int connectEstablished(int fd);
        void connectDestroy();

        void setState(int state)
        { state_ = state; }

        void setRequest(ETHandleRequest *request) { request_ = request; }
        ETHandleRequest *getRequest() { return request_; }

        int send(char *data, int size);

    private:
        ETWatcher watcher_;
        ETEventLoop *eventLoop_;
        ETAcceptor *acceptor_;
        ETHandleRequest *request_;
        int fd_;
        int state_;
        char *writeData_;
        int writeSize_;
        int writeIndex_;
        char *readData_;
        int readSize_;

    }; // end class ETConnector
} // end namespace ET

#endif // ETCONNECTOR_H

