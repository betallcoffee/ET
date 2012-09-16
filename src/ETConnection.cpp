// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#include  <unistd.h>

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETBuffer.h"

using namespace ET;

ETConnection::ETConnection(ETEventLoop *eventLoop, int fd)
    : watcher_(eventLoop, fd),
    eventLoop_(eventLoop),
    inBuf_(kBufInitSize),
    outBuf_(kBufInitSize)
{
}

ETConnection::~ETConnection()
{
}

int ETConnection::send(char *data, int size)
{
    int res = 0;
    if (!watcher_.isWriting()) {
        res = ::write(watcher_.getFD(), data, size);
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
        outBuf_.write(data + res, size - res);
        if (!watcher_.isWriting()) {
            watcher_.enableWrite();
        }
    }
    return res;
}

int ETConnection::send(ETBuffer *data)
{
    outBuf_.swap(data);
    writeHandle();
}

void ETConnection::connectEstablish()
{
    watcher_.observer(this);
    watcher_.setReadEventCallback(readEvent);
    watcher_.setWriteEventCallback(writeEvent);
    watcher_.setCloseEventCallback(closeEvent);
    watcher_.setErrorEventCallback(errorEvent);
    watcher_.enableRead();
    setState(kConnStatesConnected);

    if (connectCallback_) {
        connectCallback_(ctx_, this);
    }
}

void ETConnection::connectDestroy()
{
    watcher_.disableAll();
    int fd = watcher_.getFD();
    ::close(fd);
    setState(kConnStatesDisconnected);

    if (closeCallback_) {
        closeCallback_(ctx_, this);
    }
}

void ETConnection::shutdown()
{
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
    int fd = watcher_.getFD();
    while ((size = ::read(fd, data, 4 * 1024)) > 0) {
        inBuf_.write(data, size);
    }
    if (messageCallback_) {
        messageCallback_(ctx_, this,  &inBuf_);
    }
}

void ETConnection::writeHandle()
{
    int res = 0;
    char data[4 * 1024];
    int size = 0;
    int fd = watcher_.getFD();

    while ((size = outBuf_.read(data, 4 * 1024)) > 0) {
        res = ::write(fd, data, size);
        if (res > 0) {
            outBuf_.retrieve(res);
        } else {
            break;
        }
    }

    if (outBuf_.readableBytes() == 0) {
        watcher_.disableWrite();
    }
}

void ETConnection::closeHandle()
{
}

void ETConnection::errorHandle()
{
}

