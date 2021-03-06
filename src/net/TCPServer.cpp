// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#include <stdlib.h>

#include "TCPServer.h"
#include "Connection.h"

using namespace ET;

TCPServer::TCPServer(EventLoop *eventLoop, const char *ip, unsigned short port)
    : eventLoop_(eventLoop),
      acceptor_(eventLoop, ip, port),
      state_(kServerStatesNone),
      ctx_(NULL),
      connectionCb_(NULL)
{
    acceptor_.setContext(this);
    acceptor_.setNewSocketCallback(newSocketCallback);
}

TCPServer::~TCPServer()
{
}

bool TCPServer::run()
{
    int res = acceptor_.listen();
    if (res == 0) {
        setState(kServerStatesRunning);
        while (kServerStatesRunning == state_) {
            eventLoop_->runOneLoop();
        }
    }
    return res == 0;
}

bool TCPServer::stop() {
    setState(kServerStatesStopped);
    return true;
}

void TCPServer::newSocketCallback(void *ctx, int fd)
{
    TCPServer *self = static_cast<TCPServer *>(ctx);
    self->newConnection(fd);
}

void TCPServer::newConnection(int fd)
{
    Connection *conn = new Connection(eventLoop_, fd);
    if (connectionCb_) {
        connectionCb_(ctx_, conn);
    }
    conn->connectEstablish();
}

