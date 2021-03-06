#include "EchoServer.h"

#include "ET.h"

using namespace ET;
using namespace ET::EXAMPLES;

EchoServer::EchoServer(EventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new TCPServer(eventLoop, ip, port))
{
}

EchoServer::~EchoServer()
{
}

int EchoServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int EchoServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void EchoServer::connectionCallback(void *ctx, Connection *conn)
{
    EchoServer *self = static_cast<EchoServer *>(ctx);
    self->connection(conn);
}

void EchoServer::connection(Connection *conn)
{
    conn->setContext(this);
    conn->setReadDataCallback(messageCallback);
}

void EchoServer::messageCallback(void *ctx, Connection *conn)
{
    EchoServer *self = static_cast<EchoServer *>(ctx);
    self->message(conn);
}

void EchoServer::message(Connection *conn)
{
    conn->send(conn->readBuf());
}

