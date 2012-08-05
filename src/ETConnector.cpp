// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETConnector.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "ETEventLoop.h"
#include "ETWatcher.h"

using namespace ET;

ETConnector::ETConnector(ETEventLoop *eventLoop, int sockFD)
{
    eventLoop_ = eventLoop;
    state_ = connStatesConnecting;
    watcher_ = new ETWatcher(eventLoop, sockFD);
    watcher_->setParam(this);
    watcher_->setWriteCallback(ETConnector::handWrite);
    watcher_->setReadCallback(ETConnector::handRead);
    watcher_->setErrorCallback(ETConnector::handError);
    watcher_->setCloseCallback(ETConnector::handClose);
}

ETConnector::~ETConnector()
{
    if (watcher_) free(watcher_);
}

void ETConnector::connectEstablished()
{
    if (state_ == connStatesConnecting) {
        watcher_->enableReading();
        setState(connStatesConnected);
        if (connectCallback_) {
            connectCallback_(this);
        }
    }
}

void ETConnector::connectDestroy()
{
    if (state_ == connStatesConnected) {
        watcher_->disableAll();
        setState(connStatesDisconnected);
        if (connectCallback_) {
            connectCallback_(this);
        }
    }
}

void ETConnector::send(char *data, int length)
{
    int res = 0;
    if (!watcher_->isWriting()) {
        res = ::send(watcher_->getFD(), data, length, 0);
        if (res < 0) {
            if (errno != EWOULDBLOCK) {
                // printf error!
            }
            res = 0;
        }
    }
    if (length - res > 0) {
        writeLength_ = length - res;
        writeIndex_ = 0;
        writeData_ = (char*)malloc(length * sizeof(char));
        memcpy(writeData_, data + res, length);
        if (!watcher_->isWriting()) {
            watcher_->enableWriting();
        }
    } else if (writeCompleteCallback_) {
        writeCompleteCallback_(this);
    }
}

void ETConnector::handWrite(void *param)
{
    ETConnector *connector = (ETConnector *)param;
    connector->handWrite();
}

void ETConnector::handWrite()
{
    int res = 0;
    if (watcher_->isWriting()) {
        res = ::send(watcher_->getFD(), writeData_ + writeIndex_, writeLength_, 0);
        if (res < 0 ) {
            if (errno != EWOULDBLOCK) {
                // printf error!
            }
            res = 0;
        }
        
        if (writeLength_ - res > 0) {
            writeLength_ = writeLength_ - res;
            writeIndex_ = writeIndex_ + res;
        } else {
            watcher_->disableWriting();
            writeLength_ = 0;
            writeIndex_ = 0;
            if (writeData_) {
                free(writeData_);
                writeData_ = NULL;
            }
            if (writeCompleteCallback_) {
                writeCompleteCallback_(this);
            }
        }
    }
}

void ETConnector::handRead(void *param)
{
    ETConnector *connector = (ETConnector *)param;
    connector->handRead();
}

void ETConnector::handRead()
{
    int size = 0;
    int res = 0;
    ioctl(watcher_->getFD(), FIONREAD, &size);
    if (size > 0) {
        readData_ = (char*)malloc(size * sizeof(char));
        res = recv(watcher_->getFD(), readData_, size, 0);
        if (res != size) {
            // printf error
        } else if (readCallback_) {
            readCallback_(this, readData_, size);
            free(readData_);
            readData_ = NULL;
        }
    } else {
        // printf error
    }
}

void ETConnector::handError(void *param)
{
    ETConnector *connector = (ETConnector *)param;
    connector->handError();
    // printf error
}

void ETConnector::handError()
{
}

void ETConnector::handClose(void *param)
{
    ETConnector *connector = (ETConnector *)param;
    connector->handClose();
}

void ETConnector::handClose()
{
    watcher_->disableAll();
    setState(connStatesDisconnected);
    if (connectCallback_) {
        connectCallback_(this);
    }
}
