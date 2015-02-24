#include <map>
#include <string>
#include <stdlib.h>

#include "EventLoop.h"
#include "Connection.h"
#include "BufferV.h"
#include "TCPServer.h"
#ifdef EPOLL
#include "EpollSelect.h"
#else
#include "KqueueSelect.h"
#endif

using namespace ET;

std::map<std::string, std::string> userMap;

std::string getUser(const std::string &user)
{
    std::string res("No such user\r\n");
    std::map<std::string, std::string>::iterator it;
    it = userMap.find(user);
    if(it != userMap.end()) {
        res = it->second;
    }
    return res;
}

void onMessage(void *ctx, Connection *conn)
{
    if (conn->readBuf().findCRLF()) {
        std::string str(conn->readBuf().beginRead(), conn->readBuf().readableBytes());
        std::string data = getUser(str);
        conn->send(data.c_str(), data.length());
        conn->shutdown();
    }
}

void newConnection(void *ctx, Connection *conn)
{
    conn->setReadDataCallback(onMessage);
}

int main()
{
    userMap["liangliang"] = std::string("Welcom here!");
#ifdef EPOLL
    EpollSelect select;
#else
    KqueueSelect select;
#endif
    EventLoop eventLoop(&select);
    TCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.setConnectionCb(newConnection);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
