// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "EventLoop.h"

#include "Select.h"
#include "Watcher.h"

using namespace ET;

EventLoop::EventLoop(Select *select) : select_(select)
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::runOneLoop()
{
    int timeout = 1000;
    std::vector<Watcher*>::iterator it;

    activeWatcherList_.clear();
    select_->select(timeout, &activeWatcherList_);

    for (it = activeWatcherList_.begin(); it != activeWatcherList_.end(); ++it)
    {
        (*it)->handleEvent();
    }
}

void EventLoop::removeWatcher(Watcher *w)
{
    select_->removeWatcher(w);
}

int EventLoop::updateWatcher(Watcher *w)
{
    return select_->updateWatcher(w);
}

