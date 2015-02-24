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
    class DaytimeServer 
    {
    public:
        DaytimeServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~DaytimeServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);

        // ETConnection callback.
        static void connectCallback(void *ctx, Connection *conn);
        void connect(Connection *conn);

        TCPServer *tcpServer_;

    }; // end class ETDaytimeServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETDAYTIMESERVER_H

