#include <stdlib.h>
#include "EventLoop.h"
#include "Acceptor.h"
#include "KqueueSelect.h"
#include "HandleFactory.h"

using namespace ET;

int main(int argc, char *args[])
{
    EventLoop *eventLoop;
    Acceptor *acceptor;
    KqueueSelect *select;
    HandleFactory *factory;
    char ip[] = "192.168.139.133";

    select = new KqueueSelect();
    eventLoop = new EventLoop(select);
    acceptor = new Acceptor(eventLoop, ip, 8080);
    factory = new HandleFactory(acceptor);
//    acceptor->setFactory(factory);
    acceptor->listen();
    while(1) {
        eventLoop->runOneLoop();
    }
    free(factory);
    free(acceptor);
    free(eventLoop);

    return 0;
}
