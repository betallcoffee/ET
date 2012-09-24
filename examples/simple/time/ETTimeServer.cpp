#include <string>

#include "ETTimeServer.h"

#include "ETEventLoop.h"
#include "ETConnection.h"
#include "ETTCPServer.h"
#include "utility/ETTimestamp.h"

using namespace ET;
using namespace ET::EXAMPLES;

ETTimeServer::ETTimeServer(ETEventLoop *eventLoop, const char *ip, unsigned short port) 
    : tcpServer_(new ETTCPServer(eventLoop, ip, port))
{
}

ETTimeServer::~ETTimeServer()
{
}

int ETTimeServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int ETTimeServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void ETTimeServer::connectionCallback(void *ctx, ETConnection *conn)
{
    ETTimeServer *self = static_cast<ETTimeServer *>(ctx);
    self->connection(conn);
}

void ETTimeServer::connection(ETConnection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
}

void ETTimeServer::connectCallback(void *ctx, ETConnection *conn)
{
    ETTimeServer *self = static_cast<ETTimeServer *>(ctx);
    self->connect(conn);
}

void ETTimeServer::connect(ETConnection *conn)
{
    if (conn->isConnected()) {
        std::string now = ETTimestamp::now().toString();
        conn->send(now.c_str(), now.length());
        conn->shutdown();
    }
}

