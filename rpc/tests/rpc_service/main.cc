#include "echo.pb.h"
#include "rpc/RpcService.h"
#include <iostream>
#include <unistd.h>

namespace echo
{

class EchoServiceImpl : public EchoService
{
public:
    virtual void Echo(::google::protobuf::RpcController* controller,
                        const ::echo::EchoRequest* request,
                        ::echo::EchoResponse* response,
                        ::google::protobuf::Closure* done)
    {
        //LOG_INFO << "EchoServiceImpl::Solve";
        response->set_payload(request->payload());
        // done->Run();
    }
};

}  // namespace echo

int main(int argc, char* argv[])
{
    if (argc > 1) {
        LOG_INFO << "pid = " << getpid();
        RpcService s(argv[1]);
        echo::EchoServiceImpl echoImpl;
        s.registerService(&echoImpl);
        s.start();
    } else printf("Usage: %s XML_file \n", argv[0]);
}
