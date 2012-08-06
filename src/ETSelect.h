// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file.

#ifndef ETSELECT_H
#define ETSELECT_H

#include <vector>
#include "ETConfig.h"

namespace ET
{

class ETWatcher;
class ETEventLoop;

//
// Base class for I/O Multiplexing
//
    class ETSelect
    {
    public:
    typedef std::vector<ETWatcher *> WatcherList;

    ETSelect();
    virtual ~ETSelect();

    // Demultiplexing the I/O events
    // Must be called in the loop thread.
    virtual int select(int timeout, WatcherList *activeList) {}

    // add or update a watcher on a particular fd
    virtual int addWatcher(ETWatcher *w) = 0;

    // remove a watcher on a particular fd
    virtual int removeWatcher(ETWatcher *w) = 0;

    // update a watcher on a particular fd
    virtual int updateWatcher(ETWatcher *w) = 0;
    };
}
#endif // ETSelect
