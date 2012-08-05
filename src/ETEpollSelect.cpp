// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

#include "ETEpollSelect.h"

#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#include <map>

#include "ETWatcher.h"

using namespace ET;

ETEpollSelect::ETEpollSelect()
{
    /// epoll_create need kernel >= 2.6, glibc >= 2.3.2
    /// epoll_create1 need kernel >= 2.6.27, glibc >= 2.9
    epollfd_ = epoll_create(EPOLL_CLOEXEC);

    if (epollfd_ < 0)
    {
        //printf("ETEpollSelect::ETEpollSelect\n");
    }
}

ETEpollSelect::~ETEpollSelect()
{
    /// Not checking the return value of close is common but nevertheless serious programming error
    close(epollfd_);
}

/// Dispatch the I/O events
/// Must be called in the loop thread.
int ETEpollSelect::select(int timeout, WatcherList *activeList)
{
    int res = -1;
    /// Wait of I/O events on the epoll file descriptor of epollfd_.
    /// Wait for the maximum time of timeout.
    res = epoll_wait(epollfd_, events_, evSize_, timeout);

    if (res == -1)
    {
        /// EINTR indicates epoll_wait was interrupted by a signal handler before
        /// any of the requested events occurred or the timeout expired.
        if (errno != EINTR)
        {
            return -1;
        }
        return 0;
    }

    /// Check what of the reqeusted events occurred on the file descriptors.
    for (int i = 0; i < res; ++i)
    {
        ETWatcher *w = (ETWatcher*)events_[i].data.ptr;
        int events = 0;
        int what = events_[i].events;
        w->setActiveEvents(events);
        activeList->push_back(w);
    }
    return 0;
}

/// Add a watcher on a particular fd
void ETEpollSelect::addWatcher(ETWatcher *w)
{
    struct epoll_event event;
    
    if (watcherList_.find(w->getFD()) != watcherList_.end())
    {
        updateWatcher(w);
    }
    else
    {
    event.events |= w->getEvents();
    event.events |= EPOLLET;
    event.data.ptr = w;
    
    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, w->getFD(), &event) < 0)
    {
        //printf("epoll_ctl op=EPOLL_CTL_ADD error\n");
    }
    else
    {
        watcherList_[w->getFD()] = w;
    }
    }
}

/// Remove a watcher on a particular fd
void ETEpollSelect::removeWatcher(ETWatcher *w)
{
    struct epoll_event event;
    std::map<int, ETWatcher *>::iterator it;

    if ((it = watcherList_.find(w->getFD())) != watcherList_.end())
    {
        /// Since Linux 2.6.9, event can be specified as NULL 
        /// when using EPOLL_CTL_DEL. Applications that need
        /// to be portable to kernels before 2.6.9 shuold specify
        /// a non-NULL pointer in event.
        event.events |= w->getEvents();
        event.events |= EPOLLET;
        event.data.ptr = w;

        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, w->getFD(), &event) < 0)
        {
            //printf("epoll_ctl op=EPOLL_CTL_DEL error\n");
        }
        else
        {
            watcherList_.erase(it);
        }
    }
}

/// Update a watcher on a particular fd
void ETEpollSelect::updateWatcher(ETWatcher *w)
{
    struct epoll_event event;
    std::map<int, ETWatcher *>::iterator it;

    if ((it = watcherList_.find(w->getFD())) != watcherList_.end())
    {
        event.events |= w->getEvents();
        event.events |= EPOLLET;
        event.data.ptr = w;

        if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, w->getFD(), &event) < 0)
        {
            //printf("epoll_ctl op=EPOLL_CTL_MOD error\n");
        }
    }
    else
    {
        addWatcher(w);
    }
}
