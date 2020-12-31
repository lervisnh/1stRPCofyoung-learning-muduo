#include "base/Logger.h"
#include "net/InetAddress.h"
#include "rpc/RpcClient.h"
#include "echo.pb.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc < 2){
        printf("Usage: %s host_ip port \n", argv[0]);
        return 0;
    }

    Logger::setLogLevel(Logger::DEBUG);
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();

    InetAddress serverAddr(argv[1], atoi(argv[2]));
    echo::EchoService_Stub echoStub(new RpcClient(serverAddr));

    echo::EchoRequest req;
    req.set_payload("lile echo");

    echo::EchoResponse rsp;
    echoStub.Echo(NULL, &req, &rsp, NULL);

    std::cout << "\n Response = " << rsp.payload() << "\n" << std::endl;

    return 1;
}
