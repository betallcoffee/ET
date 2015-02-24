// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an public header file, you can include this file.
//

#ifndef ETHANDLEREQUEST_H
#define ETHANDLEREQUEST_H

namespace ET
{
    class HandleFactory;
    class Connector;
    
    //
    // class for handle the data
    //
    class HandleRequest
    {
    public:
        HandleRequest(HandleFactory *, Connector *);
        virtual ~HandleRequest();

        virtual void handle(char *readData, int size);

        void setConn(Connector *conn) { conn_ = conn; }
        Connector *getConn() { return conn_; }

    private:
        HandleFactory *factory_;
        Connector *conn_;

    }; // end class ETHandleRequest
} // end namespace ET

#endif // ETHANDLEREQUEST_H

