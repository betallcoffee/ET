#ifndef ETDISCARDSERVER_H
#define ETDISCARDSERVER_H

namespace ET
{

    class EventLoop;
    class Connection;
    class TCPServer;
    class BufferV;
    
namespace EXAMPLES
{
    class DiscardServer 
    {
    public:
        DiscardServer(EventLoop *eventLoop, const char *ip, unsigned short port);
        ~DiscardServer();

        int run();
        int isRunning();

    private:
        // TCPServer callback.
        static void connectionCallback(void *ctx, Connection *conn);
        void connection(Connection *conn);

        // Connection callback.
        static void messageCallback(void *ctx, Connection *conn);
        void message(Connection *conn);

        TCPServer *tcpServer_;

    }; // end class ETDiscardServer

} // end namespace ET::EXAMPLES

} // end namespace ET

#endif // end ETDISCARDSERVER_H

