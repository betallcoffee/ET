// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.

#ifndef ETEVENTLOOP_H
#define ETEVENTLOOP_H

#include "net/Net.h"
#include "net/Select.h"

namespace ET
{

///
/// class for event loop
///
    class EventLoop
    {
    public:
        EventLoop(Select *);
        ~EventLoop();

        // accessor of select.
        void setSelect(Select *select) { select_ = select; }
        Select *getSelect() { return select_; }

        void runOneLoop();

        void removeWatcher(Watcher *w);
        int updateWatcher(Watcher *w);

    private:
        Select *select_;
        Select::WatcherList activeWatcherList_;
    };
} // end namespace ET
#endif // ETEVENTLOOP_H
