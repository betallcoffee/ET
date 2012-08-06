// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "ETConnector.h"
#include "ETEventLoop.h"
#include "ETAcceptor.h"
#include "ETHandleRequest.h"

using namespace ET;

ETConnector::ETConnector(ETEventLoop *eventLoop, ETAcceptor *acceptor)
    : watcher_(eventLoop, kInvalidFD),
      eventLoop_(eventLoop),
      acceptor_(acceptor),
      request_(NULL),
      fd_(kInvalidFD),
      state_(kConnStatesNone),
      writeData_(NULL),
      writeSize_(0),
      writeIndex_(0),
      readData_(NULL),
      readSize_(0)
{
}

ETConnector::~ETConnector()
{
    if (writeData_) {
        free(writeData_);
    }
    if (readData_) {
        free(readData_);
    }
    if (fd_ != kInvalidFD) {
        close(fd_);
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
    int size = 0;
    int res = 0;
    ioctl(fd_, FIONREAD, &size);
    if (size > 0) {
        readData_ = (char*)malloc(size * sizeof(char));
        res = ::recv(fd_, readData_, size, 0);
        if (res != size) {
            // printf error
        } else if (request_) {
            request_->handle(readData_, size);
            free(readData_);
            readData_ = NULL;
        }
    } else {
        // printf error
    }
}

void ETConnector::writeHandle()
{
    int res = 0;
    if (watcher_.isWriting()) {
        res = ::send(fd_, writeData_ + writeIndex_, writeSize_, 0);
        if (res < 0 ) {
            if (errno != EWOULDBLOCK) {
                // printf error!
            }
            res = 0;
        }
        
        if (writeSize_ - res > 0) {
            writeSize_ = writeSize_ - res;
            writeIndex_ = writeIndex_ + res;
        } else {
            watcher_.disableWrite();
            writeSize_ = 0;
            writeIndex_ = 0;
            if (writeData_) {
                free(writeData_);
                writeData_ = NULL;
            }
            // The ETConnector object has detached from ETHandelReqeust,
            // so calling connectDestroy() to clean it.
            if (state_ == kConnStatesDisconnecting) {
               connectDestroy();
            }
        }
    }
}

void ETConnector::closeHandle()
{
    watcher_.disableAll();
    setState(kConnStatesDisconnected);
}

void ETConnector::errorHandle()
{
}

int ETConnector::connectEstablished(int fd)
{
    int res = -1;
    if (fd != kInvalidFD && state_ == kConnStatesNone) {
        fd_ = fd;
        watcher_.observer(this);
        watcher_.setFD(fd_);
        watcher_.setReadEventCallback(readEvent);
        watcher_.setWriteEventCallback(writeEvent);
        watcher_.setCloseEventCallback(closeEvent);
        watcher_.setErrorEventCallback(errorEvent);

        eventLoop_->addWatcher(&watcher_);
        res = watcher_.enableRead();
        if (!res) {
            setState(kConnStatesConnected);
        }
    }
    return res;
}

void ETConnector::connectDestroy()
{
    if (state_ == kConnStatesConnecting) {
        // If there is data that has not sent out,
        // so just change state to |connStatesDisconnecting|.
        // When the all data has sent out, calling the ETAcceptor::cleanConn;
        // If not, close stocket and change state to |connStatesDisconnected|,
        // calling the ETAcceptor::cleanConn.
        if (writeSize_ > 0){
            setState(kConnStatesDisconnecting);
        } else {
            watcher_.disableAll();
            watcher_.setFD(kInvalidFD);
            close(fd_);
            fd_ = kInvalidFD;
            setState(kConnStatesDisconnected);
            acceptor_->cleanConn(this);
        }
    }
}

int ETConnector::send(char *data, int size)
{
    int res = 0;
    if (!watcher_.isWriting()) {
        res = ::send(fd_, data, size, 0);
        if (res < 0) {
            if (errno != EWOULDBLOCK) {
                // printf error!
            }
            res = 0;
        }
    }
    if (size - res > 0) {
        writeSize_ = size - res;
        writeIndex_ = 0;
        writeData_ = (char*)malloc(size * sizeof(char));
        memcpy(writeData_, data + res, size);
        if (!watcher_.isWriting()) {
            watcher_.enableWrite();
        }
    }
    return size;
}


