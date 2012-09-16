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
#include <arpa/inet.h>

#include "ETAcceptor.h"

#include "ETLoop.h"
#include "ETWatcher.h"

using namespace ET;

ETAcceptor::ETAcceptor(ETEventLoop *eventLoop, const char *ip, unsigned short port)
    : watcher_(NULL),
      eventLoop_(eventLoop)
{
    listenning_ = 0;
    int fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    
    if (fd < 0) {
        // printf error;
    } else {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        if (ip == NULL) {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            addr.sin_addr.s_addr = inet_addr(ip);
        }
        int res = ::bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
        if (res < 0) {
            // printf error;
            close(fd);
            fd = kInvalidFD;
        } else {
            watcher_ = new ETWatcher(eventLoop_, fd);
        }
    }
}

ETAcceptor::~ETAcceptor()
{
}

void ETAcceptor::readEvent(void *arg)
{
    ETAcceptor *self = static_cast<ETAcceptor *>(arg);
    self->readHandle();
}

void ETAcceptor::writeEvent(void *arg)
{
    ETAcceptor *self = static_cast<ETAcceptor *>(arg);
    self->writeHandle();
}

void ETAcceptor::closeEvent(void *arg)
{
    ETAcceptor *self = static_cast<ETAcceptor *>(arg);
    self->closeHandle();
}

void ETAcceptor::errorEvent(void *arg)
{
    ETAcceptor *self = static_cast<ETAcceptor *>(arg);
    self->errorHandle();
}

void ETAcceptor::readHandle()
{
    int newFD;
    struct sockaddr addr;
    socklen_t addrlen = sizeof(addr);
    newFD = ::accept(watcher_->getFD(), &addr, &addrlen);
    if (newFD >= 0) {
        int flags = fcntl(newFD, F_GETFL, 0);
        flags |= O_NONBLOCK;
        fcntl(newFD, F_SETFL, flags);

        if (newConnectionCallback_) {
            newConnectionCallback_(ctx_, newFD);
        } else {
            ::close(newFD);
        }
    } else {
        int saveErrno = errno;
        switch (saveErrno) {
            case EINTR:
            case EAGAIN:
            case ECONNABORTED:
            case EFAULT:
            case EINVAL:
            case EMFILE:
            case ENOBUFS:
            case ENOMEM:
                break;

            case EBADF:
            case ENOTSOCK:
            case EOPNOTSUPP:
            case EPROTO:
                break;

            default:
                break;
        }
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

int ETAcceptor::listen()
{
    listenning_ = 1;
    int res = ::listen(watcher_->getFD(), kMaxConn);
    if (res < 0) {
        // print error
    } else {
        // enable the read event for listen socket
        watcher_->observer(this);
        watcher_->setReadEventCallback(readEvent);
        watcher_->setWriteEventCallback(writeEvent);
        watcher_->setCloseEventCallback(closeEvent);
        watcher_->setErrorEventCallback(errorEvent);
        res = watcher_->enableRead();
    }
    return res;
}

