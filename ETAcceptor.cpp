// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETAcceptor.h"

#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "ETLoop.h"

#define MAXCONN 128

using namespace ET;

ETAcceptor::ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port)
{
    eventLoop_ = eventLoop;
    listenning_ = 0;
    watcher_ = NULL;
    sockFD_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    
    if (sockFD_ < 0) {
        // printf error;
    } else {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip);
        int res = bind(sockFD_, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
        if (res < 0) {
            // printf error;
            close(sockFD_);
            sockFD_ = -1;
        } else {
            watcher_ = new ETWatcher(eventLoop_, sockFD_);
            watcher_->setParam(this);
            watcher_->setReadCallback(ETAcceptor::handRead);
        }
    }
}

ETAcceptor::~ETAcceptor()
{
    if (watcher_) free(watcher_);
    close(sockFD_);
}

int ETAcceptor::listen()
{
    listenning_ = 1;
    int res = ::listen(sockFD_, MAXCONN);
    if (res < 0) {
        // print error
        close(sockFD_);
        sockFD_ = -1;
    } else {
        // enable the read event for listen socket
        watcher_->enableReading();
    }
    return sockFD_;
}

void ETAcceptor::handRead(void *param)
{
    ETAcceptor *acceptor = (ETAcceptor *)param;
    acceptor->handRead();
}

void ETAcceptor::handRead()
{
    int res;
    struct sockaddr addr;
    socklen_t addrlen = sizeof(addr);
    res = ::accept(sockFD_, &addr, &addrlen);
    if (res < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK &&
                errno != ECONNABORTED &&
                errno != EINTR) {
            // printf error!
        }
    } else {
        int flags = fcntl(sockFD_, F_GETFL, 0);
        flags |= O_NONBLOCK;
        fcntl(sockFD_, F_SETFL, flags);
        if (newConnectCallback_) {
            newConnectCallback_(param_, res);
        } else {
            close(res);
        }
    }
}
