// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "Connector.h"
#include "EventLoop.h"
#include "Connector.h"

using namespace ET;

Connector::Connector(EventLoop *eventLoop, const char *ip, short port)
    : watcher_(NULL),
      eventLoop_(eventLoop),
      state_(kConnStatesDisconnected)
{
    bzero(&serverAddr_, sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(port);
}

Connector::~Connector()
{
    bzero(&serverAddr_, sizeof(serverAddr_));
    if (watcher_)
    {
        delete watcher_;
    }
}

void Connector::readEvent(void *arg)
{
    Connector *self = static_cast<Connector *>(arg);
    self->readHandle();
}

void Connector::writeEvent(void *arg)
{
    Connector *self = static_cast<Connector *>(arg);
    self->writeHandle();
}

void Connector::closeEvent(void *arg)
{
    Connector *self = static_cast<Connector *>(arg);
    self->closeHandle();
}

void Connector::errorEvent(void *arg)
{
    Connector *self = static_cast<Connector *>(arg);
    self->errorHandle();
}

void Connector::readHandle()
{
}

void Connector::writeHandle()
{
    if (state_ == kConnStatesConnecting) {
        watcher_->disableAll();
        int fd = watcher_->getFD();
        if (newConnectionCallback_) {
            newConnectionCallback_(ctx_, fd);
        }
    }
}

void Connector::closeHandle()
{
}

void Connector::errorHandle()
{
}

void Connector::connect()
{
    if (state_ == kConnStatesNone ||
        state_ == kConnStatesDisconnected) {
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        int flags = ::fcntl(fd, F_GETFL, 0);
        if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
            ::close(fd);
            return;
        }

        setState(kConnStatesConnect);
        if (fd < 0) {
            setState(kConnStatesDisconnected);
            return ;
        } else {
            int ret = ::connect(fd, (struct sockaddr *)&serverAddr_, sizeof(struct sockaddr_in));
            if (ret == 0) {
                setState(kConnStatesConnected);
                int fd = watcher_->getFD();
                if (newConnectionCallback_) {
                    newConnectionCallback_(ctx_, fd);
                }
                return;
            }
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

void Connector::discard()
{
    setState(kConnStatesNone);
}

void Connector::connecting(int fd)
{
    if (state_ == kConnStatesConnect) {
        if (watcher_) {
            delete watcher_;
            watcher_ = NULL;
        }
        watcher_ = new Watcher(eventLoop_, fd);
        watcher_->observer(this);
        watcher_->setWriteEventCallback(writeEvent);
        watcher_->setErrorEventCallback(errorEvent);
        watcher_->enableWrite();
        setState(kConnStatesConnecting);
    }
}

void Connector::reConnect(int fd)
{
    // TODO retry connect
    ::close(fd);
    setState(kConnStatesDisconnected);
}

