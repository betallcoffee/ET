// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include "ETEventLoop.h"

#include "ETSelect.h"
#include "ETWatcher.h"

using namespace ET;

ETEventLoop::ETEventLoop()
{
}

ETEventLoop::~ETEventLoop()
{
}

void ETEventLoop::runLoop()
{
    int timeout = 0;
    std::vector<ETWatcher*>::iterator it;
    running = 1;

    while (running)
    {
        activeWatcherList_.clear();
        select_->select(timeout, &activeWatcherList_);

        for (it = activeWatcherList_.begin(); it != activeWatcherList_.end(); ++it)
        {
            (*it)->handleEvent();
        }
    }
}

void ETEventLoop::quitLoop()
{
    running = 0;
}

int ETEventLoop::isRunning()
{
    return running;
}

void ETEventLoop::addWatcher(ETWatcher *w)
{
    select_->addWatcher(w);
}

void ETEventLoop::removeWatcher(ETWatcher *w)
{
    select_->removeWatcher(w);
}

void ETEventLoop::updateWatcher(ETWatcher *w)
{
    select_->updateWatcher(w);
}

