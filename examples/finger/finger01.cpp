#include "EventLoop.h"
#ifdef EPOLL
#include "EpollSelect.h"
#else
#include "KqueueSelect.h"
#endif

using namespace ET;

int main()
{
#ifdef EPOLL
    EpollSelect select;
#else
    KqueueSelect select;
#endif

    EventLoop eventLoop(&select);
    while(true) {
        eventLoop.runOneLoop();
    }
    return 0;
}

