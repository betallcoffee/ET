#include <map>
#include <string>
#include <stdlib.h>

#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETBufferV.h"
#include "ETTCPServer.h"

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

void onMessage(void *ctx, ETConnection *conn, ETBufferV *msg)
{
    if ( msg->findCRLF()) {
        std::string str(msg->beginRead(), msg->readableBytes());
        std::string data = getUser(str);
        conn->send(data.c_str(), data.length());
        conn->shutdown();
    }
}

void newConnection(void *ctx, ETConnection *conn)
{
    conn->setMessageCallback(onMessage);
}

int main()
{
    userMap["liangliang"] = std::string("Welcom here!");
    ETEpollSelect select;
    ETEventLoop eventLoop(&select);
    ETTCPServer tcpServer(&eventLoop, NULL, 8080);
    tcpServer.setConnectionCb(newConnection);
    tcpServer.run();
    while (true) {
        eventLoop.runOneLoop();
    }
    return 0;
}
