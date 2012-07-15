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
        virtual ~ETWatcher();

        virtual void readHandle();
        virtual void writeHandle();
        virtual void closeHandle();
        virtual void errorHandle();
        
        //  fd_ accessor.
        int getFD() { return fd_; }
        void setFD(int fd);

        // Get owner eventLoop.
        ETEventLoop *ownerLoop() { return eventLoop_; }

        // Set activeEvents_
        void setActiveEvents(int events) { activeEvents_ = events; }
        // Get events_
        int getEvents() { return events_; }

        int enableRead() { events_ |= kRead; return update(); }
        int enableWrite() { events_ |= kWrite; return update(); }
        int disableWrite() { events_ &= ~kWrite; return update(); }
        int disableAll() { events_ = kNone; return update(); }
        bool isWriting() { return events_ & kWrite; }
        
    protected:
        ETEventLoop *eventLoop_;
        int fd_;

    private:
        friend class ETEventLoop;

        void handleEvent();
        int update();

        int events_;
        int activeEvents_;
    };
} // namespace ET
#endif // ETWATCHER_H
