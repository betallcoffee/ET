// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#include "ETEpollSelect.h"
#include "ETWatcher.h"

using namespace ET;

// EPOLLHUP: Hang up happended on the associated file descriptor.
// EPOLLERR: Error condition happened on the associated file descriptor.
// EPOLLIN: the associated file is available for read operations.
// EPOLLPRI: there is urgent data available for read operations
// EPOLLOUT: the associated file is available for write operations.

ETEpollSelect::ETEpollSelect()
{
    // epoll_create need kernel >= 2.6, glibc >= 2.3.2
    // epoll_create1 need kernel >= 2.6.27, glibc >= 2.9
    epollfd_ = epoll_create(EPOLL_CLOEXEC);

    if (epollfd_ < 0)
    {
        //printf("ETEpollSelect::ETEpollSelect\n");
    }
}

ETEpollSelect::~ETEpollSelect()
{
    // Not checking the return value of close is common but nevertheless serious programming error
    close(epollfd_);
}

// Demultiplexing the I/O events
// Must be called in the loop thread.
int ETEpollSelect::select(int timeout, WatcherList *activeList)
{
    int res = -1;
    // Wait of I/O events on the epoll file descriptor of epollfd_.
    // Wait for the maximum time of timeout.
    res = epoll_wait(epollfd_, events_, evSize_, timeout);

    if (res == -1)
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
    for (int i = 0; i < res; ++i)
    {
        ETWatcher *w = (ETWatcher*)events_[i].data.ptr;
        int events = 0;
        int what = events_[i].events;

        if (what & (EPOLLIN | EPOLLPRI)) 
        {
            events |= kRead;
        }
        if (what & EPOLLOUT)
        {
            events |= kWrite;
        }
        if (what & EPOLLERR)
        {
            events |= kError;
        }
        if (what & EPOLLHUP)
        {
            events |= kClose;
        }

        w->setActiveEvents(events);
        activeList->push_back(w);
    }
    return 0;
}

// Add a watcher on a particular fd.
int ETEpollSelect::addWatcher(ETWatcher *w)
{
    struct epoll_event event;
    int events = w->getEvents();
     
    if (events & kRead)
    {
        event.events |= EPOLLIN;
    }
    if (events & kWrite)
    {
        event.events |= EPOLLOUT;
    }
    event.data.ptr = w;
    
    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, w->getFD(), &event) < 0)
    {
        //printf("epoll_ctl op=EPOLL_CTL_ADD error\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

// Remove a watcher on a particular fd.
int ETEpollSelect::removeWatcher(ETWatcher *w)
{
    // Since Linux 2.6.9, event can be specified as NULL 
    // when using EPOLL_CTL_DEL. Applications that need
    // to be portable to kernels before 2.6.9 shuold specify
    // a non-NULL pointer in event.
    struct epoll_event event;
    int events = w->getEvents();
     
    if (events & kRead)
    {
        event.events |= EPOLLIN;
    }
    if (events & kWrite)
    {
        event.events |= EPOLLOUT;
    }
    event.data.ptr = w;

    if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, w->getFD(), &event) < 0)
    {
        // EEXIST the supplied file descriptor fd is already registered with this epoll instance.
        //printf("epoll_ctl op=EPOLL_CTL_DEL error\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

// Update a watcher on a particular fd.
int ETEpollSelect::updateWatcher(ETWatcher *w)
{
    struct epoll_event event;
    int events = w->getEvents();
     
    if (events & kRead)
    {
        event.events |= EPOLLIN;
    }
    if (events & kWrite)
    {
        event.events |= EPOLLOUT;
    }
    event.data.ptr = w;

    if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, w->getFD(), &event) < 0)
    {
        // ENOENT fd is not register with this epoll instance.
        //printf("epoll_ctl op=EPOLL_CTL_DEL error\n");
        return -1;
    }
    else
    {
        return 0;
    }
}