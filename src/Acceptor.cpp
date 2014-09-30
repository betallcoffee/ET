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

#include "Acceptor.h"

#include "Loop.h"
#include "Watcher.h"

using namespace ET;

Acceptor::Acceptor(EventLoop *eventLoop, const char *ip, unsigned short port)
    : watcher_(NULL),
      eventLoop_(eventLoop)
{
    listenning_ = 0;
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    int flags = ::fcntl(fd, F_GETFL, 0);
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        ::close(fd);
        return;
    }
    
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
            watcher_ = new Watcher(eventLoop_, fd);
        }
    }
}

Acceptor::~Acceptor()
{
}

void Acceptor::readEvent(void *arg)
{
    Acceptor *self = static_cast<Acceptor *>(arg);
    self->readHandle();
}

void Acceptor::writeEvent(void *arg)
{
    Acceptor *self = static_cast<Acceptor *>(arg);
    self->writeHandle();
}

void Acceptor::closeEvent(void *arg)
{
    Acceptor *self = static_cast<Acceptor *>(arg);
    self->closeHandle();
}

void Acceptor::errorEvent(void *arg)
{
    Acceptor *self = static_cast<Acceptor *>(arg);
    self->errorHandle();
}

void Acceptor::readHandle()
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

void Acceptor::writeHandle()
{
}

void Acceptor::closeHandle()
{
}

void Acceptor::errorHandle()
{
}

int Acceptor::listen()
{
    listenning_ = 1;
    int res = ::listen(watcher_->getFD(), kMaxConn);
    if (res < 0) {
        printf("listen errorno: %s\n", strerror(errno));
        // print error
    } else {
        // enable the read event for listen socket
        watcher_->observer(this);
        watcher_->setReadEventCallback(readEvent);
        watcher_->setWriteEventCallback(writeEvent);
        watcher_->setCloseEventCallback(closeEvent);
        watcher_->setErrorEventCallback(errorEvent);
        res = watcher_->enableRead();
        if (res < 0) {
            printf("listen socket enable read error: %s\n", strerror(errno));
        }
    }
    return res;
}

