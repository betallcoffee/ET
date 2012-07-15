// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//


#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "ETConnector.h"
#include "ETEventLoop.h"
#include "ETAcceptor.h"
#include "ETHandleRequest.h"

using namespace ET;

ETConnector::ETConnector(ETEventLoop *eventLoop, int sockFD, ETAcceptor *acceptor)
    : ETWatcher(eventLoop, sockFD),
      acceptor_(acceptor),
      request_(NULL),
      state_(kConnStatesConnecting),
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
}

void ETConnector::connectEstablished()
{
    if (state_ == kConnStatesConnecting) {
        enableRead();
        setState(kConnStatesConnected);
    }
}

void ETConnector::connectDestroy()
{
    if (state_ == kConnStatesConnected || state_ == kConnStatesDisconnecting) {
        // If there is data that has not sent out,
        // so just change state to |connStatesDisconnecting|.
        // When the all data has sent out, calling the ETAcceptor::cleanConn;
        // If not, close stocket and change state to |connStatesDisconnected|,
        // calling the ETAcceptor::cleanConn.
        if (writeSize_ > 0){
            setState(kConnStatesDisconnecting);
        } else {
            setFD(kInvalidFD);
            setState(kConnStatesDisconnected);
            acceptor_->cleanConn(this);
        }
    }
}

int ETConnector::send(char *data, int size)
{
    int res = 0;
    if (!isWriting()) {
        res = ::send(getFD(), data, size, 0);
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
        if (!isWriting()) {
            enableWrite();
        }
    }
    return size;
}

void ETConnector::writeHandle()
{
    int res = 0;
    if (isWriting()) {
        res = ::send(getFD(), writeData_ + writeIndex_, writeSize_, 0);
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
            disableWrite();
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

void ETConnector::readHandle()
{
    int size = 0;
    int res = 0;
    ioctl(getFD(), FIONREAD, &size);
    if (size > 0) {
        readData_ = (char*)malloc(size * sizeof(char));
        res = recv(getFD(), readData_, size, 0);
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

void ETConnector::closeHandle()
{
    disableAll();
    setState(kConnStatesDisconnected);
}

void ETConnector::errorHandle()
{
}

