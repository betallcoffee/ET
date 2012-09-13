// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//

#include "ETTCPServer.h"
#include "ETConnection.h"

using namespace ET;

ETTCPServer::ETTCPServer(ETEventLoop *eventLoop, const char *ip, unsigned short port)
    : eventLoop_(eventLoop),
      acceptor_(eventLoop, ip, port),
      state_(kServerStatesNone)
{
    acceptor_.setContext(this);
    acceptor_.setNewConnectionCallback(newConnectionCallback);
}

ETTCPServer::~ETTCPServer()
{
}

int ETTCPServer::run()
{
    int res = acceptor_.listen();
    if (res == 0) {
        setState(kServerStatesRunning);
    }
    return res;
}

void ETTCPServer::newConnectionCallback(void *ctx, int fd)
{
    ETTCPServer *self = static_cast<ETTCPServer *>(ctx);
    self->newConnection(fd);
}

void ETTCPServer::newConnection(int fd)
{
    ETConnection *conn = new ETConnection(eventLoop_, fd);
    if (connectionCb_) {
        connectionCb_(ctx_, conn);
        conn->setContext(ctx_);
        conn->connectEstablish();
    } else {
        delete conn;
    }
}

