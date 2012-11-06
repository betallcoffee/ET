#ifndef ETDISCARDSERVER_H
#define ETDISCARDSERVER_H

namespace ET
{

    class ETEventLoop;
    class ETConnection;
    class ETTCPServer;
    class ETBufferV;
    
namespace EXAMPLES
{
    class ETDiscardServer 
    {
    public:
        ETDiscardServer(ETEventLoop *eventLoop, const char *ip, unsigned short port);
        ~ETDiscardServer();

        int run();
        int isRunning();

    private:
        // ETTCPServer callback.
        static void connectionCallback(void *ctx, ETConnection *conn);
        void connection(ETConnection *conn);

        // ETConnection callback.
        static void messageCallback(void *ctx, ETConnection *conn, ETBufferV *msg);
        void message(ETConnection *conn, ETBufferV *msg);

        ETTCPServer *tcpServer_;

    }; // end class ETDiscardServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETDISCARDSERVER_H

