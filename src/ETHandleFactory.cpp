// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETAcceptor.h"
#include "ETHandleFactory.h"
#include "ETHandleRequest.h"

using namespace ET;

ETHandleFactory::ETHandleFactory(ETAcceptor *acceptor) : acceptor_(acceptor)
{
}

ETHandleRequest *ETHandleFactory::makeRequest(ETConnector *conn)
{
    ETHandleRequest *request = new ETHandleRequest(this);
    request->setConn(conn);
    return request;
}

// it will be called in ETHandleRequest deconstruct function.
void ETHandleFactory::cleanRequest(ETHandleRequest *request)
{
    acceptor_->cleanRequest(request);
}

