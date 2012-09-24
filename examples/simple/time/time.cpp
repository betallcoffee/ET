#include "ETTimeServer.h"

// ET lib headers
#include "ETEventLoop.h"
#include "ETEpollSelect.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    ETEpollSelect select;
    ETEventLoop eventLoop(&select);
    ETTimeServer echoServer(&eventLoop, NULL, 8080);
    echoServer.run();
    while(true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
