// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file.

#ifndef ETWATCHER_H
#define ETWATCHER_H

namespace ET
{

class ETEventLoop;

typedef std::vector<ETWatcher*> WatcherList;

///
/// A selectable I/O Wathcer.
///
/// This class own the file descriptor.
/// The file descriptor could be a socket,
/// an eventfd, a timerfd, or a signalfd
    class ETWatcher
    {
    public:
        typedef (*EventCallback)();

        ETWatcher(ETEventLoop *eventLoop, int fd);
        ~ETWatcher();

        /// Get fd_.
        int getFD() { return fd_; }

        /// Get owner eventLoop.
        ETEventLoop *ownerLoop() { return eventLoop_; }

        /// Set activeEvents_
        void setAcitveEvents(int events) { activeEvents_ = events; }
        /// Get events_
        int getEvents() { return events_; }

        void setReadCallback(EventCallback cb) { readCallback_ = cb; }
        void setWriteCallback(EventCallback cb) { writeCallback_ = cb; }
        void setCloseCallback(EventCallback cb) { closeCalback_ = cb; }
        void setErrorCallback(EventCallback cb) { errorCallback_ = cb; }

        void enableReading() { events_ |= READ; update(); }
        void enableWriting() { events_ |= WRITE; update(); }
        void disableWriting() { events_ &= ~WRITE; update(); }
        int isWriting() { return events_ & WRITE; }
        void disableAll() { events_ = NONE; update(); }
        void handleEvent();
        
    private:
        void update();

        static const int NONE;
        static const int READ;
        static const int WRITE;
        static const int CLOSE;
        static const int ERROR;

        ETEventLoop *eventLoop_;
        const int fd_;
        int events_;
        int activeEvents_;
        EventCallback readCallback_;
        EventCallback writeCallback_;
        EventCallback closeCallback_;
        EventCallback errorCallback_;
    };
} // namespace ET
#endif // ETWATCHER_H
