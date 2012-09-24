#include <stdio.h>

// ET lib headers
#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETBuffer.h"
#include "ETTCPServer.h"

using namespace ET;

const int kBufSize = 1024 * 40;
const char *gFile = NULL;

void onMessage(void *ctx, ETConnection *conn, ETBuffer *msg)
{
}

void onWriteComplete(void *ctx, ETConnection *conn)
{
    FILE *file = static_cast<FILE *>(conn->getArg());
    if (file) {
        char buf[kBufSize];
        int n = ::fread(buf, 1, kBufSize, file);
        if (n > 0) {
            conn->send(buf, n);
        } else {
            ::fclose(file);
            file = NULL;
            conn->setArg(file);
            conn->shutdown();
        }
    }
}

void onClose(void *ctx, ETConnection *conn)
{
}

void onConnect(void *ctx, ETConnection *conn)
{
    if (conn->isConnected()) {
        FILE *file = ::fopen(gFile, "rb");
        if (file) {
            conn->setArg(file);
            char buf[kBufSize];
            int n = ::fread(buf, 1, kBufSize, file);
            conn->send(buf, n);
        } else {
            conn->shutdown();
        }
    }
}

void newConnection(void *ctx, ETConnection *conn)
{
//    conn->setMessageCallback(onMessage);
    conn->setWriteCompleteCallback(onWriteComplete);
    conn->setConnectCallback(onConnect);
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        gFile = argv[1];
        ETEpollSelect select;
        ETEventLoop eventLoop(&select);
        ETTCPServer tcpServer(&eventLoop, NULL, 8080);
        tcpServer.setConnectionCb(newConnection);
        tcpServer.run();
        while(true) {
            eventLoop.runOneLoop();
        }
    }
    return 0;
}

