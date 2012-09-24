#ifndef ETDAYTIMESERVER_H
#define ETDAYTIMESERVER_H

namespace ET
{

    class ETEventLoop;
    class ETConnection;
    class ETTCPServer;
    class ETBuffer;
    
namespace EXAMPLES
{
    class ETTimeServer 
    {
    public:
        ETTimeServer(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETTimeServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, ETConnection *conn);
        void connection(ETConnection *conn);

        // ETConnection callback.
        static void connectCallback(void *ctx, ETConnection *conn);
        void connect(ETConnection *conn);

        ETTCPServer *tcpServer_;

    }; // end class ETTimeServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETDAYTIMESERVER_H
