#include "DiscardServer.h"

#include "EventLoop.h"
#include "Connection.h"
#include "TCPServer.h"

using namespace ET;
using namespace ET::EXAMPLES;

DiscardServer::DiscardServer(EventLoop *eventLoop, const char *ip, unsigned short port)
    : tcpServer_(new TCPServer(eventLoop, ip, port))
{
}

DiscardServer::~DiscardServer()
{
}

int DiscardServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int DiscardServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void DiscardServer::connectionCallback(void *ctx, Connection *conn)
{
    DiscardServer *self = static_cast<DiscardServer *>(ctx);
    self->connection(conn);
}

void DiscardServer::connection(Connection *conn)
{
    conn->setContext(this);
    conn->setReadDataCallback(messageCallback);
}

void DiscardServer::messageCallback(void *ctx, Connection *conn)
{
    DiscardServer *self = static_cast<DiscardServer *>(ctx);
    self->message(conn);
}

void DiscardServer::message(Connection *conn)
{
    conn->readBuf().clear();
}

