// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an interal header file, you should not include this file.

#ifndef ETEVENTLOOP_H
#define ETEVENTLOOP_H

#include <vector>

namespace ET
{

class ETSelect;
class ETWatcher;

///
/// class for event loop
///
    class ETEventLoop
    {
    public:
        ETEventLoop();
        ~ETEventLoop();

        void runLoop();
        void quitLoop();
        int isRunning();

        void addWatcher(ETWatcher *w);
        void removeWatcher(ETWatcher *w);
        void updateWatcher(ETWatcher *w);

    private:
        ETSelect *select_;
        int running;
        std::vector<ETWatcher*> activeWatcherList_;


    };
} // end namespace ET
#endif // ETEVENTLOOP_H
