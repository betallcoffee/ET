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
    : eventLoop_(eventLoop),
      fd_(fd),
      events_(kNoneEvent),
      activeEvents_(kNoneEvent)
{
}

ETWatcher::~ETWatcher()
{
}

void ETWatcher::setFD(int fd) 
{ 
    disableAll();
    activeEvents_ = kNoneEvent;
    fd_ = fd; 
}

void ETWatcher::handleEvent()
{
    if (observer_ == NULL)
    {
        return ;
    }

    if (activeEvents_ & kCloseEvent)
    {
        if (closeEvent_) closeEvent_(observer_);
    }
    if (activeEvents_ & kErrorEvent)
    {
        if (errorEvent_) errorEvent_(observer_);
    }
    if (activeEvents_ & kReadEvent)
    {
        if (readEvent_) readEvent_(observer_);
    }
    if (activeEvents_ & kWriteEvent)
    {
        if (writeEvent_) writeEvent_(observer_);
    }
}

int ETWatcher::update()
{
    return eventLoop_->updateWatcher(this);
}

