// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETWatcher.h"

#include <sys/epoll.h>

#include "ETEventLoop.h"

using namespace ET;

/// EPOLLHUP: Hang up happended on the associated file descriptor.
/// EPOLLERR: Error condition happened on the associated file descriptor.
/// EPOLLIN: the associated file is available for read operations.
/// EPOLLPRI: there is urgent data available for read operations
/// EPOLLOUT: the associated file is available for write operations.
const int ETWatcher::NONE = 0;
const int ETWatcher::READ = EPOLLIN | EPOLLPRI;
const int ETWatcher::WRITE = EPOLLOUT;
const int ETWatcher::ERROR = EPOLLERR;
const int ETWatcher::CLOSE = EPOLLHUP;

ETWatcher::ETWatcher(ETEventLoop *eventLoop, int fd)
    : eventLoop_(eventLoop),
      fd_(fd),
      events_(0),
      activeEvents_(0)
{
}

ETWatcher::~ETWatcher()
{
}

void ETWatcher::handleEvent()
{
    if (activeEvents_ & CLOSE)
    {
        if (closeCallback_) closeCallback_();
    }
    if (activeEvents_ & ERROR)
    {
        if (errorCallback_) errorCallback_();
    }
    if (activeEvents_ & READ)
    {
        if (readCallback_) readCallback_();
    }
    if (activeEvents_ & WRITE)
    {
        if (writeCallback_) writeCallback_();
    }
}

void ETWatcher::update()
{
    eventLoop_->updateWatcher(this);
}

