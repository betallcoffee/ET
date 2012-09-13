#include <stdlib.h>
#include "ETEventLoop.h"
#include "ETAcceptor.h"
#include "ETEpollSelect.h"
#include "ETHandleFactory.h"

using namespace ET;

int main(int argc, char *args[])
{
    ETEventLoop *eventLoop;
    ETAcceptor *acceptor;
    ETEpollSelect *select;
    ETHandleFactory *factory;
    char ip[] = "192.168.139.133";

    select = new ETEpollSelect();
    eventLoop = new ETEventLoop(select);
    acceptor = new ETAcceptor(eventLoop, ip, 8080);
    factory = new ETHandleFactory(acceptor);
    acceptor->setFactory(factory);
    acceptor->listen();
    while(1) {
        eventLoop->runOneLoop();
    }
    free(factory);
    free(acceptor);
    free(eventLoop);

    return 0;
}
