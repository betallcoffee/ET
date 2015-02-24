#include "ChargenServer.h"

#include "EventLoop.h"
#include "Connection.h"
#include "TCPServer.h"

using namespace ET;
using namespace ET::EXAMPLES;

ChargenServer::ChargenServer(EventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new TCPServer(eventLoop, ip, port))
{
}

ChargenServer::~ChargenServer()
{
}

int ChargenServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ChargenServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ChargenServer::connectionCallback(void *ctx, Connection *conn)
{
    ChargenServer *self = static_cast<ChargenServer *>(ctx);
    self->connection(conn);
}

void ChargenServer::connection(Connection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
    conn->setReadDataCallback(messageCallback);
    conn->setWriteCompleteCallback(writeCompleteCallback);
}

void ChargenServer::connectCallback(void *ctx, Connection *conn)
{
    ChargenServer *self = static_cast<ChargenServer *>(ctx);
    self->connect(conn);
}

void ChargenServer::connect(Connection *conn)
{
    char data[] = { "hello wolrd!" };
    if (conn->isConnected()) {
        conn->send(data, sizeof(data));
    }
}

void ChargenServer::messageCallback(void *ctx, Connection *conn)
{
    ChargenServer *self = static_cast<ChargenServer *>(ctx);
    self->message(conn);
}

void ChargenServer::message(Connection *conn)
{
	conn->readBuf().clear();
}

void ChargenServer::writeCompleteCallback(void *ctx, Connection *conn)
{
    ChargenServer *self = static_cast<ChargenServer *>(ctx);
    self->writeComplete(conn);
}

void ChargenServer::writeComplete(Connection *conn)
{
    char data[] = { "@ET" };
    conn->send(data, sizeof(data));
}

