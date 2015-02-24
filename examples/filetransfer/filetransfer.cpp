#include <stdio.h>

// ET lib headers
#include "EventLoop.h"
#include "Connection.h"
#include "Buffer.h"
#include "TCPServer.h"
#ifdef EPOLL
#include "EpollSelect.h"
#else
#include "KqueueSelect.h"
#endif

using namespace ET;

const int kBufSize = 1024 * 40;
const char *gFile = NULL;

void onMessage(void *ctx, Connection *conn)
{
}

void onWriteComplete(void *ctx, Connection *conn)
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

void onClose(void *ctx, Connection *conn)
{
}

void onConnect(void *ctx, Connection *conn)
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

void newConnection(void *ctx, Connection *conn)
{
//    conn->setMessageCallback(onMessage);
    conn->setWriteCompleteCallback(onWriteComplete);
    conn->setConnectCallback(onConnect);
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        gFile = argv[1];
#ifdef EPOLL
    EpollSelect select;
#else
    KqueueSelect select;
#endif
        EventLoop eventLoop(&select);
        TCPServer tcpServer(&eventLoop, NULL, 8080);
        tcpServer.setConnectionCb(newConnection);
        tcpServer.run();
        while(true) {
            eventLoop.runOneLoop();
        }
    }
    return 0;
}

