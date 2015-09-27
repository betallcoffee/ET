// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file.

#ifndef ETSELECT_H
#define ETSELECT_H

#include <vector>
#include "Config.h"

namespace ET
{

class Watcher;
class EventLoop;

//
// Base class for I/O Multiplexing
//
    class Select
    {
    public:
    typedef std::vector<Watcher *> WatcherList;

    Select();
    virtual ~Select();

    // Demultiplexing the I/O events
    // Must be called in the loop thread.
    virtual int select(int timeout, WatcherList *activeList) { return 0;}

    // remove a watcher on a particular fd
    virtual int removeWatcher(Watcher *w) = 0;

    // update a watcher on a particular fd
    virtual int updateWatcher(Watcher *w) = 0;
    };
}
#endif // Select
