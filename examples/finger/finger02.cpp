#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETTCPServer.h"

using namespace ET;

int main() 
{
    ETEpollSelect select;
    ETEventLoop eventLoop(&select);
    ETTCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
