// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETHandleRequest.h"
#include "ETHandleFactory.h"
#include "ETConnector.h"

using namespace ET;

ETHandleRequest::ETHandleRequest(ETHandleFactory *factory, ETConnector *conn)
    : factory_(factory),
      conn_(conn)
{
}

ETHandleRequest::~ETHandleRequest()
{
    factory_->cleanRequest(this);
}

void ETHandleRequest::handle(char *readData, int size)
{
    conn_->send(readData, size);
}

