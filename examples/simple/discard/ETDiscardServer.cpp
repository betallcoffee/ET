#include "ETDiscardServer.h"

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETTCPServer.h"

using namespace ET;
using namespace ET::EXAMPLES;

ETDiscardServer::ETDiscardServer(ETEventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new ETTCPServer(eventLoop, ip, port))
{
}

ETDiscardServer::~ETDiscardServer()
{
}

int ETDiscardServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ETDiscardServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ETDiscardServer::connectionCallback(void *ctx, ETConnection *conn)
{
    ETDiscardServer *self = static_cast<ETDiscardServer *>(ctx);
    self->connection(conn);
}

void ETDiscardServer::connection(ETConnection *conn)
{
    conn->setContext(this);
    conn->setMessageCallback(messageCallback);
}

void ETDiscardServer::messageCallback(void *ctx, ETConnection *conn, ETBufferV *msg)
{
    ETDiscardServer *self = static_cast<ETDiscardServer *>(ctx);
    self->message(conn, msg);
}

void ETDiscardServer::message(ETConnection *conn, ETBufferV *msg)
{
    msg->clear();
}

