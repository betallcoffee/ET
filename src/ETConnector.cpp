// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "ETConnector.h"
#include "ETEventLoop.h"
#include "ETAcceptor.h"

using namespace ET;

ETConnector::ETConnector(ETEventLoop *eventLoop, const char *ip, short port)
    : watcher_(NULL),
      eventLoop_(eventLoop),
      state_(kConnStatesDisconnected)
{
    bzero(&serverAddr_, sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(port);
}

ETConnector::~ETConnector()
{
    bzero(&serverAddr_, sizeof(serverAddr_));
    if (watcher_)
    {
        delete watcher_;
    }
}

void ETConnector::readEvent(void *arg)
{
    ETConnector *self = static_cast<ETConnector *>(arg);
    self->readHandle();
}

void ETConnector::writeEvent(void *arg)
{
    ETConnector *self = static_cast<ETConnector *>(arg);
    self->writeHandle();
}

void ETConnector::closeEvent(void *arg)
{
    ETConnector *self = static_cast<ETConnector *>(arg);
    self->closeHandle();
}

void ETConnector::errorEvent(void *arg)
{
    ETConnector *self = static_cast<ETConnector *>(arg);
    self->errorHandle();
}

void ETConnector::readHandle()
{
}

void ETConnector::writeHandle()
{
    if (state_ == kConnStatesConnecting) {
        watcher_->disableAll();
        int fd = watcher_->getFD();
        if (newConnectionCallback_) {
            newConnectionCallback_(ctx_, fd);
        }
    }
}

void ETConnector::closeHandle()
{
}

void ETConnector::errorHandle()
{
}

void ETConnector::connect()
{
    if (state_ == kConnStatesNone ||
        state_ == kConnStatesDisconnected) {
        int fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        setState(kConnStatesConnect);
        if (fd < 0) {
            setState(kConnStatesDisconnected);
            return ;
        } else {
            int res = ::connect(fd, (struct sockaddr *)&serverAddr_, sizeof(struct sockaddr_in));
            int saveErrno = errno;
            switch(saveErrno) {
                case EINPROGRESS:
                case EINTR:
                case EISCONN:
                case EALREADY:
                    connecting(fd);
                    break;
                    
                case EAGAIN:
                case EADDRINUSE:
                case ECONNREFUSED:
                case ENETUNREACH:
                    reConnect(fd);
                    break;

                case EACCES:
                case EPERM:
                case EAFNOSUPPORT:
                case EBADF:
                case EFAULT:
                case ENOTSOCK:
                    ::close(fd);
                    setState(kConnStatesDisconnected);
                    break;

                default:
                    ::close(fd);
                    setState(kConnStatesDisconnected);
                    break;
            }
        }
    }
}

void ETConnector::discard()
{
    setState(kConnStatesNone);
}

void ETConnector::connecting(int fd)
{
    if (state_ == kConnStatesConnect) {
        if (watcher_) {
            delete watcher_;
            watcher_ = NULL;
        }
        watcher_ = new ETWatcher(eventLoop_, fd);
        watcher_->observer(this);
        watcher_->setWriteEventCallback(writeEvent);
        watcher_->setErrorEventCallback(errorEvent);
        watcher_->enableWrite();
        setState(kConnStatesConnecting);
    }
}

void ETConnector::reConnect(int fd)
{
    ::close(fd);
    setState(kConnStatesDisconnected);
}

