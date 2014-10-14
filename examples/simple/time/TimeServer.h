#ifndef ETDAYTIMESERVER_H
#define ETDAYTIMESERVER_H

namespace ET
{

    class EventLoop;
    class Connection;
    class TCPServer;
    class Buffer;
    
namespace EXAMPLES
{
    class TimeServer
    {
    public:
        TimeServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~TimeServer();

        int run();
        int isRunning();

    private:
        // TCPServer callback.
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);

        // Connection callback.
        static void connectCallback(void *ctx, Connection *conn);
        void connect(Connection *conn);

        TCPServer *tcpServer_;

    }; // end class ETTimeServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETDAYTIMESERVER_H

