// Use of this source code is governed by a BSD-style license
// that can be found in the license file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.
//

#include "ETServer.h"

#include <stdlib.h>

#include "ETEventLoop.h"
#include "ETAcceptor.h"
#include "ETConnector.h"

using namespace ET;

ETServer::ETServer(char *ip, unsigned short port)
{
    eventLoop_ = new ETEventLoop();
    acceptor_ = new ETAcceptor(eventLoop_, ip, port);
    acceptor_->setParam(this);
    acceptor_->setNewConnectCallback(ETServer::newConnector);
    state_ = serverStatesStopped;
}

ETServer::~ETServer()
{
    free(eventLoop_);
    free(acceptor_);
}

void ETServer::start()
{
    state_ = serverStatesRunning;
    acceptor_->listen();
}

void ETServer::newConnector(void *param, int fd)
{
    ETServer *server = (ETServer *)param;
    server->newConnector(fd);
}

void ETServer::newConnector(int fd)
{
    ETConnector *connector = new ETConnector(eventLoop_, fd);
    connector->setReadCallback(readCallback_);
    connector->setWriteCompleteCallback(writeCompleteCallback_);
    connector->setConnectCallback(connectCallback_);

    connectorList_[fd] = connector;
    connector->connectEstablished();
}
