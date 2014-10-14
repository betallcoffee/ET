#include <string>

#include "TimeServer.h"

#include "EventLoop.h"
#include "Connection.h"
#include "TCPServer.h"
#include "utility/Timestamp.h"

using namespace ET;
using namespace ET::EXAMPLES;

TimeServer::TimeServer(EventLoop *eventLoop, const char *ip, unsigned short port)
    : tcpServer_(new TCPServer(eventLoop, ip, port))
{
}

TimeServer::~TimeServer()
{
}

int TimeServer::run()
{
    tcpServer_->setContext(this);
    tcpServer_->setConnectionCb(connectionCallback);
    return tcpServer_->run();
}

int TimeServer::isRunning()
{
    return tcpServer_->isRunning(); 
}

void TimeServer::connectionCallback(void *ctx, Connection *conn)
{
    TimeServer *self = static_cast<TimeServer *>(ctx);
    self->connection(conn);
}

void TimeServer::connection(Connection *conn)
{
    conn->setContext(this);
    conn->setConnectCallback(connectCallback);
}

void TimeServer::connectCallback(void *ctx, Connection *conn)
{
    TimeServer *self = static_cast<TimeServer *>(ctx);
    self->connect(conn);
}

void TimeServer::connect(Connection *conn)
{
    if (conn->isConnected()) {
        std::string now = Timestamp::now().toString();
        conn->send(now.c_str(), now.length());
        conn->shutdown();
    }
}

