// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an public header file, you can include this file.
//

#ifndef ETHANDLEFACTORY_H
#define ETHANDLEFACTORY_H

namespace ET
{
    class ETAcceptor;
    class ETConnector;
    class ETHandleRequest;
    //
    // class for ETHandleRequest factory method
    //
    class ETHandleFactory
    {
    public:
        ETHandleFactory(ETAcceptor *);
        virtual ~ETHandleFactory() {}

        virtual ETHandleRequest *makeRequest(ETConnector *);
        virtual void cleanRequest(ETHandleRequest *);
    private:
        ETAcceptor *acceptor_;

    }; // end class ETHandleFactory
} // end namespace ET

#endif // ETHANDLEFACTORY_H
