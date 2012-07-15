// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//


#include <sys/epoll.h>
#include <unistd.h>

#include "ETWatcher.h"
#include "ETEventLoop.h"

using namespace ET;

ETWatcher::ETWatcher(ETEventLoop *eventLoop, int fd)
    : fd_(fd),
      eventLoop_(eventLoop),
      events_(kNone),
      activeEvents_(kNone)
{
}

ETWatcher::~ETWatcher()
{
    close(fd_);
}

void ETWatcher::setFD(int fd) 
{ 
    disableAll();
    activeEvents_ = kNone;
    close(fd_);
    fd_ = fd; 
}

void ETWatcher::readHandle()
{
}

void ETWatcher::writeHandle()
{
}

void ETWatcher::closeHandle()
{
}

void ETWatcher::errorHandle()
{
}

void ETWatcher::handleEvent()
{
    if (activeEvents_ & kClose)
    {
        this->closeHandle();
    }
    if (activeEvents_ & kError)
    {
        this->errorHandle();
    }
    if (activeEvents_ & kRead)
    {
        this->readHandle();
    }
    if (activeEvents_ & kWrite)
    {
        this->writeHandle();
    }
}

int ETWatcher::update()
{
    return eventLoop_->updateWatcher(this);
}

