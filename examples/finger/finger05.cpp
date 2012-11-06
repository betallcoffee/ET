#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETBufferV.h"
#include "ETTCPServer.h"

using namespace ET;

void onMessage(void *ctx, ETConnection *conn, ETBufferV *msg)
{
    if (msg->findCRLF() >= 0) {
        char data[] = { "No such user\r\n" };
        conn->send(data, sizeof(data));
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
