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

#include "Log.h"

#include "Connection.h"
#include "EventLoop.h"
#include "Watcher.h"

using namespace ET;

Connection::Connection(EventLoop *eventLoop, int fd)
    : state_(kConnStatesNone),
    watcher_(new Watcher(eventLoop, fd)),
    eventLoop_(eventLoop),
    arg_(NULL),
    ctx_(NULL),
    readDataCallback_(NULL),
    writeCompleteCallback_(NULL),
    closeCallback_(NULL),
    connectCallback_(NULL)
{
    LogD("Init a connection(%d)", watcher_->getFD());
}

Connection::~Connection()
{
    if (watcher_ != NULL) {
        LogD("Destroy a connection(%d)", watcher_->getFD());
        delete watcher_;
    } else {
        LogD("Destroy a connection");
    }
}

size_t Connection::send(const char *data, size_t size)
{
    ssize_t res = 0;
    if (state_ != kConnStatesConnected) {
        return -1;
    }

    if (!watcher_->isWriting() && outBuf_.empty()) {
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

size_t Connection::send(BufferV &data)
{
    if (state_ != kConnStatesConnected) {
        return -1;
    }
    
    size_t res = send(data.beginRead(), data.readableBytes());

    return res;
}

void Connection::lock()
{
    // TODO
}

void Connection::unlock()
{
    // TODO
}

void Connection::connectEstablish()
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

void Connection::connectClose()
{
    closeHandle();
}

void Connection::shutdown()
{
    setState(kConnStatesDisconnecting);
    shutdownWrite();
}

void Connection::readEvent(void *arg)
{
    Connection *self = static_cast<Connection *>(arg);
    self->readHandle();
}

void Connection::writeEvent(void *arg)
{
    Connection *self = static_cast<Connection *>(arg);
    self->writeHandle();
}

void Connection::closeEvent(void *arg)
{
    Connection *self = static_cast<Connection *>(arg);
    self->closeHandle();
}

void Connection::errorEvent(void *arg)
{
    Connection *self = static_cast<Connection *>(arg);
    self->errorHandle();
}

void Connection::readHandle()
{
    char data[4 * 1024];
    ssize_t size = 0;
    int fd = watcher_->getFD();
    size = ::read(fd, data, 4 * 1024);
    if (size == 0) {
        // Read FIN.
        closeHandle();
    } else if (size > 0) {
        do {
            inBuf_.append(data, size);
        } while ((size = ::read(fd, data, 4 * 1024)) > 0);
        if (readDataCallback_) {
            readDataCallback_(ctx_, this);
        } else {
            defaultReadData();
        }
    }
}

void Connection::writeHandle()
{
    ssize_t res = 0;
    int fd = watcher_->getFD();
    size_t size = outBuf_.readableBytes();;
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

void Connection::closeHandle()
{
    watcher_->disableAll();
    ::close(watcher_->getFD());
    setState(kConnStatesDisconnected);

    if (closeCallback_) {
        closeCallback_(ctx_, this);
    }
}

void Connection::errorHandle()
{
}

void Connection::shutdownWrite()
{
    if (!watcher_->isWriting()) {
        ::shutdown(watcher_->getFD(), SHUT_WR);
    }
}

void Connection::defaultReadData()
{
    inBuf_.clear();
}
