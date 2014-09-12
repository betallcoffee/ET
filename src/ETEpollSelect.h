// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file

#ifndef ETEPOLLSELECT_H
#define ETEPOLLSELECT_H

#include <sys/epoll.h>

#include <map>

#include "ETConfig.h"
#include "ETSelect.h"

namespace ET
{

class ETWatcher;

//
// IO Multiplexing with epoll(4)
// 

    class ETEpollSelect : public ETSelect
    {
    public:
        ETEpollSelect();
        ~ETEpollSelect();

	// Demultiplexing the I/O events
	// Must be called in the loop thread.
	    virtual int select(int timeout, WatcherList *activeList);

	// Remove a watcher on a particular fd
	    virtual int removeWatcher(ETWatcher *w);

	// Add/Update a watcher on a particular fd 
	    virtual int updateWatcher(ETWatcher *w);

    private:
        static const int kEventsSize = 1024;

        int update(int, ETWatcher *);

        int epollfd_;
        struct epoll_event *events_;
        int evSize_;
    };
}
#endif // ETEPOLLSELECT_H
