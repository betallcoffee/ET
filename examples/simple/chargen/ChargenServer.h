#ifndef ETECHOSERVER_H
#define ETECHOSERVER_H

namespace ET
{

    class EventLoop;
    class Connection;
    class TCPServer;
    class ETBufferV;
    
namespace EXAMPLES
{
    class ChargenServer 
    {
    public:
        ChargenServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~ChargenServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);

        // ETConnection callback.
        static void connectCallback(void *ctx, Connection *conn);
        void connect(Connection *conn);

        static void messageCallback(void *ctx, Connection *conn);
        void message(Connection *conn);

        static void writeCompleteCallback(void *ctx, Connection *conn);
        void writeComplete(Connection *conn);

        TCPServer *tcpServer_;

    }; // end class ETChargenServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETECHOSERVER_H

