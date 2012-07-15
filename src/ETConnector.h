// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#ifndef ETCONNECTOR_H
#define ETCONNECTOR_H

#include "ETWatcher.h"

namespace ET
{
    class ETEventLoop;
    class ETAcceptor;
    class ETHandleRequest;

enum connStates
{
    kConnStatesConnected,
    kConnStatesConnecting,
    kConnStatesDisconnected,
    kConnStatesDisconnecting
};

    ///
    /// operator for new connector
    ///
    class ETConnector : public ETWatcher
    {
    public:
        ETConnector(ETEventLoop *eventLoop, int sockFD, ETAcceptor *acceptor);
        virtual ~ETConnector();

        virtual void readHandle();
        virtual void writeHandle();
        virtual void closeHandle();
        virtual void errorHandle();

        void connectEstablished();
        void connectDestroy();

        void setState(int state)
        { state_ = state; }

        void setRequest(ETHandleRequest *request) { request_ = request; }
        ETHandleRequest *getRequest() { return request_; }

        int send(char *data, int size);

    private:
        ETAcceptor *acceptor_;
        ETHandleRequest *request_;
        int state_;
        char *writeData_;
        int writeSize_;
        int writeIndex_;
        char *readData_;
        int readSize_;

    }; // end class ETConnector
} // end namespace ET

#endif // ETCONNECTOR_H

