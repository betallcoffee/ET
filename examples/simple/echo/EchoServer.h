#ifndef ETECHOSERVER_H
#define ETECHOSERVER_H

namespace ET
{

    class EventLoop;
    class Connection;
    class TCPServer;
    class BufferV;
    
namespace EXAMPLES
{
    class EchoServer 
    {
    public:
        EchoServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~EchoServer();

        int run();
        int isRunning();

    private:
        // TCPServer callback.
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);

        // Connection callback.
        static void messageCallback(void *ctx, Connection *conn, BufferV *msg);
        void message(Connection *conn, BufferV *msg);

        TCPServer *tcpServer_;

    }; // end class EchoServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETECHOSERVER_H

