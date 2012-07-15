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
    class ETEventLoop;
    class ETHandleFactory;
    class ETHandleRequest;
    class ETConnector;

    //
    // class for operation of listenning socket fd
    //
    class ETAcceptor : public ETWatcher
    {
    public:
        ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        virtual ~ETAcceptor();

        virtual void readHandle();
        virtual void writeHandle();
        virtual void closeHandle();
        virtual void errorHandle();

        // You must set ETHandleFactory object before calling listen();
        void setFactory(ETHandleFactory *factory) { factory_ = factory; }
        ETHandleFactory *getFactory() { return factory_; }

        // the server begin to listen ip:port, and running.
        int listen();

        // Detach ETConnector from ETHandlerquest,
        // and clean ETConnector object.
        void cleanRequest(ETHandleRequest *);

        // Clean a ETConnector object, it is called in cleanRequest(ETHandleRequest*).
        // And it will be called by ETConnector::writeHandle to clean ETConnector object itself,
        // when ETConnector 
        // Now it just free the ETConnector object.
        // TODO, the ETAcceptor maintain a queue that is used for caching ETConnector objects.
        void cleanConn(ETConnector *);

    private:
        ETConnector *newConnHandle(ETEventLoop *eventLoop, int newFD);
        void *freeConnHandle(ETConnector *);

        ETHandleFactory *factory_;
        int listenning_;

    }; // end class ETAcceptor
}// end namespace ET

#endif // end ETACCEPTOR_H
