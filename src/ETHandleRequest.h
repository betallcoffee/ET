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
    class ETHandleFactory;
    class ETConnector;
    
    //
    // class for handle the data
    //
    class ETHandleRequest
    {
    public:
        ETHandleRequest(ETHandleFactory *, ETConnector *);
        virtual ~ETHandleRequest();

        virtual void handle(char *readData, int size);

        void setConn(ETConnector *conn) { conn_ = conn; }
        ETConnector *getConn() { return conn_; }

    private:
        ETHandleFactory *factory_;
        ETConnector *conn_;

    }; // end class ETHandleRequest
} // end namespace ET

#endif // ETHANDLEREQUEST_H

