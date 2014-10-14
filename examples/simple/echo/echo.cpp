#include "EchoServer.h"

// ET lib headers
#include "EventLoop.h"
#include "KqueueSelect.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    KqueueSelect select;
    EventLoop eventLoop(&select);
    EchoServer echoServer(&eventLoop, NULL, 8080);
    printf("echo server init 8080\n");
    int res = echoServer.run();
    if (res == 0) {
        printf("echo server run begin\n");
        while(true) {
            eventLoop.runOneLoop();
        }
        printf("echo server run end\n");
    } else {
        printf("echo server init error\n");
    }
    return 0;
}
