// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "ETEventLoop.h"
#include "ETWatcher.h"
#include "ETConnection.h"

using namespace ET;

ETConnection::ETConnection(ETEventLoop *eventLoop, int fd)
    : watcher_(new ETWatcher(eventLoop, fd)),
    eventLoop_(eventLoop),
    ctx_(NULL),
    messageCallback_(NULL),
    writeCompleteCallback_(NULL),
    closeCallback_(NULL),
    connectCallback_(NULL)
{
}

ETConnection::~ETConnection()
{
    if (watcher_  != NULL) {
        delete watcher_;
    }
}

int ETConnection::send(const char *data, int size)
{
    int res = 0;
    if (state_ != kConnStatesConnected) {
        return -1;
    }

    if (!watcher_->isWriting()) {
        res = ::write(watcher_->getFD(), data, size);
        if (res > 0) {
            if (res == size) {
                if (writeCompleteCallback_) {
                    writeCompleteCallback_(ctx_, this);
                }
            }
        } else {
            res = 0;
        }
    }
    
    if (res < size) {
        outBuf_.append(data + res, size - res);
        if (!watcher_->isWriting()) {
            watcher_->enableWrite();
        }
    }
    return res;
}

int ETConnection::send(ETBufferV *data)
{
    if (state_ != kConnStatesConnected) {
        return -1;
    }
    
    int res = send(data->beginRead(), data->readableBytes());

    return res;
}

void ETConnection::connectEstablish()
{
    watcher_->observer(this);
    watcher_->setReadEventCallback(readEvent);
    watcher_->setWriteEventCallback(writeEvent);
    watcher_->setCloseEventCallback(closeEvent);
    watcher_->setErrorEventCallback(errorEvent);
    watcher_->enableRead();
    setState(kConnStatesConnected);

    if (connectCallback_) {
        connectCallback_(ctx_, this);
    }
}

void ETConnection::connectClose()
{
    closeHandle();
}

void ETConnection::shutdown()
{
    setState(kConnStatesDisconnecting);
    shutdownWrite();
}

void ETConnection::readEvent(void *arg)
{
    ETConnection *self = static_cast<ETConnection *>(arg);
    self->readHandle();
}

void ETConnection::writeEvent(void *arg)
{
    ETConnection *self = static_cast<ETConnection *>(arg);
    self->writeHandle();
}

void ETConnection::closeEvent(void *arg)
{
    ETConnection *self = static_cast<ETConnection *>(arg);
    self->closeHandle();
}

void ETConnection::errorEvent(void *arg)
{
    ETConnection *self = static_cast<ETConnection *>(arg);
    self->errorHandle();
}

void ETConnection::readHandle()
{
    char data[4 * 1024];
    int size = 0;
    int fd = watcher_->getFD();
    size = ::read(fd, data, 4 * 1024);
    if (size == 0) {
        // Read FIN.
        closeHandle();
    } else if (size > 0) {
        do {
            inBuf_.append(data, size);
        } while ((size = ::read(fd, data, 4 * 1024)) > 0); 
        if (messageCallback_) {
            messageCallback_(ctx_, this,  &inBuf_);
        } else {
            defaultMessage(&inBuf_);
        }
    }
}

void ETConnection::writeHandle()
{
    int res = 0;
    int fd = watcher_->getFD();
    int size = outBuf_.readableBytes();;
    char *data = outBuf_.beginRead();

    if (watcher_->isWriting()) {
        res = ::write(fd, data, size); 
        if (res > 0) {
            outBuf_.retrieve(res);
            if (outBuf_.readableBytes() == 0) {
                watcher_->disableWrite();
                if (writeCompleteCallback_) {
                    writeCompleteCallback_(ctx_, this);
                }
                if (state_ == kConnStatesDisconnecting) {
                    shutdownWrite();
                }
            }
        } else {
        }
    }
}

void ETConnection::closeHandle()
{
    watcher_->disableAll();
    ::close(watcher_->getFD());
    delete watcher_;
    watcher_ = NULL;
    setState(kConnStatesDisconnected);

    if (closeCallback_) {
        closeCallback_(ctx_, this);
        delete this;
    }
}

void ETConnection::errorHandle()
{
}

void ETConnection::shutdownWrite()
{
    if (!watcher_->isWriting()) {
        ::shutdown(watcher_->getFD(), SHUT_WR);
    }
}

void ETConnection::defaultMessage(ETBufferV *msg)
{
    msg->clear();
}
