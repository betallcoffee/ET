// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.

#ifndef ETEVENTLOOP_H
#define ETEVENTLOOP_H

#include "ETConfig.h"
#include "ETSelect.h"

namespace ET
{

class ETWathcer;

///
/// class for event loop
///
    class ETEventLoop
    {
    public:
        ETEventLoop(ETSelect *);
        ~ETEventLoop();

        // accessor of select.
        void setSelect(ETSelect *select) { select_ = select; }
        ETSelect *getSelect() { return select_; }

        void runOneLoop();

        void addWatcher(ETWatcher *w);
        void removeWatcher(ETWatcher *w);
        int updateWatcher(ETWatcher *w);

    private:
        ETSelect *select_;
        ETSelect::WatcherList activeWatcherList_;
    };
} // end namespace ET
#endif // ETEVENTLOOP_H
