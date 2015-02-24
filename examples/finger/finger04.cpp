#include "EventLoop.h"
#include "Connection.h"
#include "BufferV.h"
#include "TCPServer.h"
#ifdef EPOLL
#include "EpollSelect.h"
#else
#include "KqueueSelect.h"
#endif

using namespace ET;

void onMessage(void *ctx, Connection *conn)
{
    if (conn->readBuf().findCRLF() >= 0) {
        conn->shutdown();
    }
}

void newConnection(void *ctx, Connection *conn)
{
    conn->setReadDataCallback(onMessage);
}

int main()
{
#ifdef EPOLL
    EpollSelect select;
#else
    KqueueSelect select;
#endif
    EventLoop eventLoop(&select);
    TCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.setConnectionCb(newConnection);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
