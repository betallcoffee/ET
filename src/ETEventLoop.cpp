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

void ETEventLoop::select()
{
    int timeout = 0;
    std::vector<ETWatcher*>::iterator it;

    activeWatcherList_.clear();
    select_->select(timeout, &activeWatcherList_);

    for (it = activeWatcherList_.begin(); it != activeWatcherList_.end(); ++it)
    {
        (*it)->handleEvent();
    }
}

void ETEventLoop::addWatcher(ETWatcher *w)
{
    select_->addWatcher(w);
}

void ETEventLoop::removeWatcher(ETWatcher *w)
{
    select_->removeWatcher(w);
}

int ETEventLoop::updateWatcher(ETWatcher *w)
{
    return select_->updateWatcher(w);
}

