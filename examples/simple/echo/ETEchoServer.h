#ifndef ETECHOSERVER_H
#define ETECHOSERVER_H

namespace ET
{

    class ETEventLoop;
    class ETConnection;
    class ETTCPServer;
    class ETBuffer;
    
namespace EXAMPLES
{
    class ETEchoServer 
    {
    public:
        ETEchoServer(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETEchoServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, ETConnection *conn);
        void connection(ETConnection *conn);

        // ETConnection callback.
        static void messageCallback(void *ctx, ETConnection *conn, ETBuffer *msg);
        void message(ETConnection *conn, ETBuffer *msg);

        ETTCPServer *tcpServer_;

    }; // end class ETEchoServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETECHOSERVER_H

