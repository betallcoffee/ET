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
    class ETChargenServer 
    {
    public:
        ETChargenServer(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETChargenServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, ETConnection *conn);
        void connection(ETConnection *conn);

        // ETConnection callback.
        static void connectCallback(void *ctx, ETConnection *conn);
        void connect(ETConnection *conn);

        static void messageCallback(void *ctx, ETConnection *conn, ETBuffer *msg);
        void message(ETConnection *conn, ETBuffer *msg);

        static void writeCompleteCallback(void *ctx, ETConnection *conn);
        void writeComplete(ETConnection *conn);

        ETTCPServer *tcpServer_;

    }; // end class ETChargenServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETECHOSERVER_H

