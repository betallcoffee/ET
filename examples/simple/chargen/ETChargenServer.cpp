#include "ETChargenServer.h"

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETTCPServer.h"

using namespace ET;
using namespace ET::EXAMPLES;

ETChargenServer::ETChargenServer(ETEventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new ETTCPServer(eventLoop, ip, port))
{
}

ETChargenServer::~ETChargenServer()
{
}

int ETChargenServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ETChargenServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ETChargenServer::connectionCallback(void *ctx, ETConnection *conn)
{
    ETChargenServer *self = static_cast<ETChargenServer *>(ctx);
    self->connection(conn);
}

void ETChargenServer::connection(ETConnection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
    conn->setMessageCallback(messageCallback);
    conn->setWriteCompleteCallback(writeCompleteCallback);
}

void ETChargenServer::connectCallback(void *ctx, ETConnection *conn)
{
    ETChargenServer *self = static_cast<ETChargenServer *>(ctx);
    self->connect(conn);
}

void ETChargenServer::connect(ETConnection *conn)
{
    char data[] = { "hello wolrd!" };
    if (conn->isConnected()) {
        conn->send(data, sizeof(data));
    }
}

void ETChargenServer::messageCallback(void *ctx, ETConnection *conn, ETBufferV *msg)
{
    ETChargenServer *self = static_cast<ETChargenServer *>(ctx);
    self->message(conn, msg);
}

void ETChargenServer::message(ETConnection *conn, ETBufferV *msg)
{
    msg->clear();
}

void ETChargenServer::writeCompleteCallback(void *ctx, ETConnection *conn)
{
    ETChargenServer *self = static_cast<ETChargenServer *>(ctx);
    self->writeComplete(conn);
}

void ETChargenServer::writeComplete(ETConnection *conn)
{
    char data[] = { "@ET" };
    conn->send(data, sizeof(data));
}

