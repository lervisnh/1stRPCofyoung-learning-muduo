
#include "rpc/RpcFrame.h"
#include "base/Logger.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        Logger::setLogLevel(Logger::TRACE);

        EventLoop listenLoop;
        InetAddress listenAddr(atoi(argv[1]));
        TcpServer IO(&listenLoop, listenAddr, "RpcFrame_test_IO");
        RpcFrame rpc_service(&listenLoop, &IO);
        rpc_service.setWorkers(3);
        rpc_service.start();
        // rpc_service.registerService();
    }
    else
    {
        printf("Usage: %s port\n", argv[0]);
    }
}
