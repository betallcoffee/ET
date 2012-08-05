// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file

#ifndef ETEPOLLSELECT_H
#define ETEPOLLSELECT_H

#include "ETSelect.h"

#include <sys/epoll.h>

#include <map>

namespace ET
{

class ETWatcher;

///
/// IO Multiplexing with epoll(4)
/// 

    class ETEpollSelect
    {
    public:
        ETEpollSelect();
	    virtual ~ETEpollSelect();

	/// Dispatch the I/O events
	/// Must be called in the loop thread.
	    virtual int select(int timeout, WatcherList *activeList);

	/// Add a watcher on a particular fd
	    virtual void addWatcher(ETWatcher *w);

	/// Remove a watcher on a particular fd
	    virtual void removeWatcher(ETWatcher *w);

	/// Update a watcher on a particular fd 
	    virtual void updateWatcher(ETWatcher *w);

    private:
        int epollfd_;
        struct epoll_event *events_;
        int evSize_;
	    std::map<int, ETWatcher *> watcherList_;
    };
}
#endif // ETEPOLLSELECT_H
