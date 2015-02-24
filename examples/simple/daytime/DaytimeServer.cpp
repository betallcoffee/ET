#include <string>

#include "DaytimeServer.h"

#include "EventLoop.h"
#include "Connection.h"
#include "TCPServer.h"
#include "utility/Timestamp.h"

using namespace ET;
using namespace ET::EXAMPLES;

DaytimeServer::DaytimeServer(EventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new TCPServer(eventLoop, ip, port))
{
}

DaytimeServer::~DaytimeServer()
{
}

int DaytimeServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int DaytimeServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void DaytimeServer::connectionCallback(void *ctx, Connection *conn)
{
    DaytimeServer *self = static_cast<DaytimeServer *>(ctx);
    self->connection(conn);
}

void DaytimeServer::connection(Connection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
}

void DaytimeServer::connectCallback(void *ctx, Connection *conn)
{
    DaytimeServer *self = static_cast<DaytimeServer *>(ctx);
    self->connect(conn);
}

void DaytimeServer::connect(Connection *conn)
{
    if (conn->isConnected()) {
        std::string now = Timestamp::now().toFormattedString();
        conn->send(now.c_str(), now.length());
        conn->shutdown();
    }
}

