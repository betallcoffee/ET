// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: betallcoffee

// This is an interal header file, you should not include this file

#ifndef ETKQUEUESELECT_H
#define ETKQUEUESELECT_H

#include <sys/event.h>

#include "ETConfig.h"
#include "ETSelect.h"

namespace ET {

    /**
     * @class ETKqueueSelect ETKqueueSelect.h "ETKqueueSelect.h"
     * @brief IO Multiplexing with kqueue(2)
     */
    class ETKqueueSelect : ETSelect {
        ETKqueueSelect();
        ~ETKqueueSelect();
        
        // Must be called in the loop thread.
	    virtual int select(int timeout, WatcherList *activeList);
        
        // Remove a watcher on a particular fd
	    virtual int removeWatcher(ETWatcher *w);
        
        // Add/Update a watcher on a particular fd
	    virtual int updateWatcher(ETWatcher *w);
        
    private:
        static const int kEventsSize = 1024;
        
        int update(int, ETWatcher *);
        
        int _kqueuefd;
        struct kevent *_events;
        int _evSize;

    };
    
}

#endif // ETKQUEUESELECT_H
