#include <map>
#include <string>
#include <stdlib.h>

#include "ETEventLoop.h"
#include "ETEpollSelect.h"
#include "ETConnection.h"
#include "ETBuffer.h"
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

void onMessage(void *ctx, ETConnection *conn, ETBuffer *msg)
{
    int res = 0;
    if ((res = msg->findCRLF()) >= 0) {
        char *user = (char *)malloc(res);
        msg->read(user, res);
        std::string str(user, res);
        std::string data = getUser(str);
        conn->send(data.c_str(), data.length());
        conn->shutdown();
        free(user);
    }
}

void newConnection(void *ctx, ETConnection *conn)
{
    conn->setMessageCallback(onMessage);
    conn->connectEstablish();
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
