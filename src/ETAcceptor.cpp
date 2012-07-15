// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "ETLoop.h"
#include "ETAcceptor.h"
#include "ETConnector.h"
#include "ETHandleRequest.h"
#include "ETHandleFactory.h"

using namespace ET;

ETAcceptor::ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port)
    : ETWatcher(eventLoop, kInvalidFD),
      factory_(NULL)
{
    listenning_ = 0;
    fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    
    if (fd_ < 0) {
        // printf error;
    } else {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip);
        int res = bind(fd_, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
        if (res < 0) {
            // printf error;
            close(fd_);
            fd_ = kInvalidFD;
        }
    }
}

ETAcceptor::~ETAcceptor()
{
    close(fd_);
}

int ETAcceptor::listen()
{
    listenning_ = 1;
    int res = ::listen(fd_, kMaxConn);
    if (res < 0) {
        // print error
        close(fd_);
        fd_ = kInvalidFD;
    } else {
        // enable the read event for listen socket

        eventLoop_->addWatcher(this);
        res = enableRead();
    }
    return res;
}

void ETAcceptor::cleanRequest(ETHandleRequest *request)
{
    ETConnector *conn = request->getConn();
    if (conn) {
        // Detach ETConnector from EThandleRequest; 
        request->setConn(NULL);
        // clean ETConnector object.
        conn->connectDestroy();
    }
}

void ETAcceptor::cleanConn(ETConnector *conn)
{
    freeConnHandle(conn);
}

ETConnector *ETAcceptor::newConnHandle(ETEventLoop *eventLoop, int newFD)
{
    return new ETConnector(eventLoop, newFD, this);
}

void *ETAcceptor::freeConnHandle(ETConnector *conn)
{
    free(conn);
}

void ETAcceptor::readHandle()
{
    int newFD;
    struct sockaddr addr;
    socklen_t addrlen = sizeof(addr);
    newFD = ::accept(fd_, &addr, &addrlen);
    if (newFD < 0) {
        if (errno != EAGAIN 
            && errno != EWOULDBLOCK 
            && errno != ECONNABORTED 
            && errno != EINTR) {
            // invoke again
        } else {
            // printf error! close fd_;
        }
    } else {
        int flags = fcntl(newFD, F_GETFL, 0);
        flags |= O_NONBLOCK;
        fcntl(newFD, F_SETFL, flags);

        ETConnector *conn = newConnHandle(eventLoop_, newFD);
        ETHandleRequest *request = factory_->makeRequest(conn);
        // Attach a ETHandleRequest object to ETConnector.
        conn->setRequest(request);
        eventLoop_->addWatcher(conn);
        conn->enableRead();
    }
}

void ETAcceptor::writeHandle()
{
}

void ETAcceptor::closeHandle()
{
}

void ETAcceptor::errorHandle()
{
}
