#include "ETEchoServer.h"

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETTCPServer.h"

using namespace ET;
using namespace ET::EXAMPLES;

ETEchoServer::ETEchoServer(ETEventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new ETTCPServer(eventLoop, ip, port))
{
}

ETEchoServer::~ETEchoServer()
{
}

int ETEchoServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ETEchoServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ETEchoServer::connectionCallback(void *ctx, ETConnection *conn)
{
    ETEchoServer *self = static_cast<ETEchoServer *>(ctx);
    self->connection(conn);
}

void ETEchoServer::connection(ETConnection *conn)
{
    conn->setContext(this);
    conn->setMessageCallback(messageCallback);
}

void ETEchoServer::messageCallback(void *ctx, ETConnection *conn, ETBufferV *msg)
{
    ETEchoServer *self = static_cast<ETEchoServer *>(ctx);
    self->message(conn, msg);
}

void ETEchoServer::message(ETConnection *conn, ETBufferV *msg)
{
    conn->send(msg);
}

