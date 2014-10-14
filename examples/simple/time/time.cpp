#include "TimeServer.h"

// ET lib headers
#include "EventLoop.h"
#include "EpollSelect.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    EpollSelect select;
    EventLoop eventLoop(&select);
    TimeServer echoServer(&eventLoop, NULL, 8080);
    echoServer.run();
    while(true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
