#include "ETEventLoop.h"
#include "ETEpollSelect.h"

using namespace ET;

int main()
{
    ETEpollSelect select;
    ETEventLoop eventLoop(&select);
    while(true) {
        eventLoop.runOneLoop();
    }
    return 0;
}

