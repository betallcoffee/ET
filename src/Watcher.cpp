// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//


#include <unistd.h>

#include "Watcher.h"
#include "EventLoop.h"

using namespace ET;

Watcher::Watcher(EventLoop *eventLoop, int fd)
    : eventLoop_(eventLoop),
      fd_(fd),
      events_(kNoneEvent),
      activeEvents_(kNoneEvent),
      state_(kWatcherStatesNew)
{
}

Watcher::~Watcher()
{
    activeEvents_ = kNoneEvent;
    eventLoop_->removeWatcher(this);
    ::close(fd_);
}

void Watcher::handleEvent()
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

int Watcher::update()
{
    return eventLoop_->updateWatcher(this);
}

