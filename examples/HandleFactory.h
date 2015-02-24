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
    class Acceptor;
    class Connector;
    class HandleRequest;
    //
    // class for ETHandleRequest factory method
    //
    class HandleFactory
    {
    public:
        HandleFactory(Acceptor *);
        virtual ~HandleFactory() {}

        virtual HandleRequest *makeRequest(Connector *);
        virtual void cleanRequest(HandleRequest *);
    private:
        Acceptor *acceptor_;

    }; // end class ETHandleFactory
} // end namespace ET

#endif // ETHANDLEFACTORY_H
