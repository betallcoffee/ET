#include <string>

#include "ETDaytimeServer.h"

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETTCPServer.h"
#include "utility/ETTimestamp.h"

using namespace ET;
using namespace ET::EXAMPLES;

ETDaytimeServer::ETDaytimeServer(ETEventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new ETTCPServer(eventLoop, ip, port))
{
}

ETDaytimeServer::~ETDaytimeServer()
{
}

int ETDaytimeServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ETDaytimeServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ETDaytimeServer::connectionCallback(void *ctx, ETConnection *conn)
{
    ETDaytimeServer *self = static_cast<ETDaytimeServer *>(ctx);
    self->connection(conn);
}

void ETDaytimeServer::connection(ETConnection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
}

void ETDaytimeServer::connectCallback(void *ctx, ETConnection *conn)
{
    ETDaytimeServer *self = static_cast<ETDaytimeServer *>(ctx);
    self->connect(conn);
}

void ETDaytimeServer::connect(ETConnection *conn)
{
    if (conn->isConnected()) {
        std::string now = ETTimestamp::now().toFormattedString();
        conn->send(now.c_str(), now.length());
        conn->shutdown();
    }
}

