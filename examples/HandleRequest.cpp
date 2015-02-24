// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "HandleRequest.h"
#include "HandleFactory.h"
#include "Connector.h"

using namespace ET;

HandleRequest::HandleRequest(HandleFactory *factory, Connector *conn)
    : factory_(factory),
      conn_(conn)
{
}

HandleRequest::~HandleRequest()
{
    factory_->cleanRequest(this);
}

void HandleRequest::handle(char *readData, int size)
{
	// TODO connection instead of connector
//    conn_->send(readData, size);
}

