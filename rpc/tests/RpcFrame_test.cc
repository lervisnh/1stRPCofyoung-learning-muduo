
#include "rpc/RpcFrame.h"
#include "base/Logger.h"

int main()
{
    Logger::setLogLevel(Logger::TRACE);

    EventLoop listenLoop;
    InetAddress listenAddr(20007);
    TcpServer IO(&listenLoop, listenAddr, "RpcFrame_test_IO");
    RpcFrame rpc_service(&listenLoop, &IO);
    rpc_service.setWorkers(1);
    rpc_service.start();
    // rpc_service.registerService();
}
