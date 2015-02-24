#include "EventLoop.h"
#include "TCPServer.h"
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
    TCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
