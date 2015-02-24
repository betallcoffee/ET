// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "Acceptor.h"
#include "HandleFactory.h"
#include "HandleRequest.h"

using namespace ET;

HandleFactory::HandleFactory(Acceptor *acceptor) : acceptor_(acceptor)
{
}

HandleRequest *HandleFactory::makeRequest(Connector *conn)
{
    HandleRequest *request = new HandleRequest(this, conn);
    request->setConn(conn);
    return request;
}

// it will be called in ETHandleRequest deconstruct function.
void HandleFactory::cleanRequest(HandleRequest *request)
{
	// TODO acceptor add cleanRequest method
//    acceptor_->cleanRequest(request);
}

