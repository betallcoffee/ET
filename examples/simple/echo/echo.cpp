#include "EchoServer.h"

// ET lib headers
#include "ET.h"

using namespace ET;
using namespace EXAMPLES;

int main()
{
    KqueueSelect select;
    EventLoop eventLoop(&select);
    EchoServer echoServer(&eventLoop, NULL, 8080);
    printf("echo server init 8080\n");
    printf("echo server run begin\n");
    if (echoServer.run()) {
        printf("echo server run end\n");
    } else {
        printf("echo server init error\n");
    }
    return 0;
}
