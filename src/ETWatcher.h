// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file.

#ifndef ETWATCHER_H
#define ETWATCHER_H

#include "ETConfig.h"

namespace ET
{

class ETEventLoop;
class ETWatcher;

enum eventType 
{
    kNoneEvent   =   0,
    kReadEvent   =   1,
    kWriteEvent  =   2,
    kCloseEvent  =   4,
    kErrorEvent  =   8
};

//
// A selectable I/O Wathcer.
//
// This class own the file descriptor.
// The file descriptor could be a socket,
// an eventfd, a timerfd, or a signalfd
//
    class ETWatcher
    {
    public:

        ETWatcher(ETEventLoop *eventLoop, int fd);
        ~ETWatcher();

        // observer.
        void rmObserver() { observer_ = 0; }
        void observer(void *observer) { observer_ = observer; }

        //  fd_ accessor.
        int getFD() { return fd_; }
        void setFD(int fd);

        // Get owner eventLoop.
        ETEventLoop *ownerLoop() { return eventLoop_; }

        // Set activeEvents_
        void setActiveEvents(int events) { activeEvents_ = events; }
        // Get events_
        int getEvents() { return events_; }

        // set callback function.
        void setReadEventCallback(EventCallback readEvent) 
        { readEvent_ = readEvent; }
        void  setWriteEventCallback(EventCallback writeEvent)
        { writeEvent_ = writeEvent; }
        void setCloseEventCallback(EventCallback closeEvent)
        { closeEvent_ = closeEvent; }
        void setErrorEventCallback(EventCallback errorEvent)
        { errorEvent_ = errorEvent; }

        int enableRead() { events_ |= kReadEvent; return update(); }
        int enableWrite() { events_ |= kWriteEvent; return update(); }
        int disableWrite() { events_ &= ~kWriteEvent; return update(); }
        int disableAll() { events_ = kNoneEvent; return update(); }
        bool isWriting() { return events_ & kWriteEvent; }

        void handleEvent();

    private:
        int update();

        void *observer_;
        EventCallback readEvent_;
        EventCallback writeEvent_;
        EventCallback closeEvent_;
        EventCallback errorEvent_;

        ETEventLoop *eventLoop_;
        int fd_;
        int events_;
        int activeEvents_;
    };
} // namespace ET
#endif // ETWATCHER_H
