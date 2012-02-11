// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file.

#ifndef ETSELECT_H
#define ETSELECT_H

#include "ETWatcher.h"

namespace ET
{

class ETEventLoop;

///
/// Base class for I/O Multiplexing
///
    class ETSelect
    {
    public:
    ETSelect();
    virtual ~ETSelect();

    /// Dispatch the I/O events
    /// Must be called in the loop thread.
    virtual int select(int timeout, WatcherList *activeList);

    /// add or update a watcher on a particular fd
    virtual void addWatcher(ETWatcher *w) = 0;

    /// remove a watcher on a particular fd
    virtual void removeWatcher(ETWatcher *w) = 0;

    /// update a watcher on a particular fd
    virtual void updateWatcher(ETWatcher *w) = 0;
    };
}
#endif // ETSelect
