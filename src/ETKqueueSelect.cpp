//
//  ETKqueueSelect.cpp
//  ET
//
//  Created by liang on 9/11/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "ETKqueueSelect.h"
#include "ETWatcher.h"

using namespace ET;

// EV_ADD         Adds the event to the kqueue.
// Re-adding an existing event will modify the parameters of the original event,
// and not result in a duplicate entry.
// Adding an event automatically enables it, unless overridden by the EV_DISABLE flag.

// EV_DELETE      Removes the event from the kqueue.
// Events which are attached to file descriptors are automatically deleted on the last close of the descriptor.

// EVFILT_READ      Takes a file descriptor as the identifier,
// and returns whenever there is data available to read.
// The behavior of the filter is slightly different depending on the descriptor type.

// EVFILT_WRITE     Takes a file descriptor as the identifier,
// and returns whenever it is possible to write to the descriptor.
// For sockets, pipes and fifos, data will contain the amount of space remaining in the write buffer.
// The filter will set EV_EOF when the reader disconnects, and for the fifo case,
// this may be cleared by use of EV_CLEAR.  Note that this filter is not supported for vnodes.
// For sockets, the low water mark and socket error handling is identical to the EVFILT_READ case.

ETKqueueSelect::ETKqueueSelect() {
    _kqueuefd = kqueue();
    if (_kqueuefd == kInvalidFD) {
        _events = NULL;
        _evSize = 0;
    } else {
        _events = (struct kevent *)malloc(sizeof(struct kevent) * kEventsSize);
        _evSize = kEventsSize;
    }
}

ETKqueueSelect::~ETKqueueSelect() {
    if (_kqueuefd != kInvalidFD) {
        close(_kqueuefd);
    }
    if (_events != NULL) {
        free(_events);
    }
}

// Demultiplexing the I/O events
// Must be called in the loop thread.
int ETKqueueSelect::select(int timeout, WatcherList *activeList) {
    int ret = -1;
    ret = kevent(_kqueuefd, NULL, 0, _events, _evSize, NULL);
    if (ret == -1)
    {
        // EINTR indicates epoll_wait was interrupted by a signal handler before
        // any of the requested events occurred or the timeout expired.
        if (errno != EINTR)
        {
            return -1;
        }
        return 0;
    }
    
    // Check what of the reqeusted events occurred on the file descriptors.
    for (int i = 0; i < ret; ++i)
    {
        ETWatcher *w = (ETWatcher *)_events[i].udata;
        int events = 0;
        int filter = _events[i].filter;
        
        if (filter == EVFILT_READ)
        {
            events |= kReadEvent;
        }
        if (filter == EVFILT_WRITE)
        {
            events |= kWriteEvent;
        }
        
        w->setActiveEvents(events);
        activeList->push_back(w);
    }
    return 0;
}

// Remove a watcher on a particular fd.
int ETKqueueSelect::removeWatcher(ETWatcher *w)
{
    int ret = 0;
    if (w->getState() == kWatcherStatesAdded)
    {
        ret = update(EV_DELETE, w);
    }
    w->setState(kWatcherStatesNew);
    return ret;
}

// Update a watcher on a particular fd.
int ETKqueueSelect::updateWatcher(ETWatcher *w)
{
    int ret = 0;
    int state = w->getState();

    if (state == kWatcherStatesNew ||
        state == kWatcherStatesDeleted)
    {
        ret = update(EV_ADD, w);
        w->setState(kWatcherStatesAdded);
    }

    return ret;
}

int ETKqueueSelect::update(int operation, ETWatcher *w)
{
    struct kevent ke;
    int filter = 0;
    int events = w->getEvents();

    bzero(&ke, sizeof(ke));
    if (events & kReadEvent)
    {
        filter = EVFILT_READ;
    }
    if (events & kWriteEvent)
    {
        filter = EVFILT_WRITE;
    }
    
    EV_SET(&ke, w->getFD(), EVFILT_WRITE, filter, 0, 0, w);
    if (kevent(_kqueuefd, &ke, 1, NULL, 0, NULL) < 0)
    {
        return -1;
    }

    return 0;
}
