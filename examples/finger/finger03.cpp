#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETTCPServer.h"

using namespace ET;

void onConnect(void *ctx, ETConnection *conn)
{
    if (conn->isConnected())
        conn->shutdown();
}

void newConnection(void *ctx, ETConnection *conn)
{
    conn->setConnectCallback(onConnect);
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
