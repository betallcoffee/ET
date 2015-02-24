#include "DiscardServer.h"

// ET lib headers
#include "EventLoop.h"
#include "KqueueSelect.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    KqueueSelect select;
    EventLoop eventLoop(&select);
    DiscardServer echoServer(&eventLoop, NULL, 8080);
    echoServer.run();
    while(true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
