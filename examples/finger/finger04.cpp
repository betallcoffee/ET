#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETBuffer.h"
#include "ETTCPServer.h"

using namespace ET;

void onMessage(void *ctx, ETConnection *conn, ETBuffer *msg)
{
    if (msg->findCRLF() >= 0) {
        conn->shutdown();
    }
}

void newConnection(void *ctx, ETConnection *conn)
{
    conn->setMessageCallback(onMessage);
}

int main()
{
    ETEpollSelect select;
    ETEventLoop eventLoop(&select);
    ETTCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.setConnectionCb(newConnection);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
