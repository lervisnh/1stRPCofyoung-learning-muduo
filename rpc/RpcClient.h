#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H

#include "net/EventLoop.h"
#include "rpc/TcpClient.h"

#include <functional>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
using namespace google::protobuf;

class RpcClient : public RpcChannel
{
public:
    RpcClient(const InetAddress&);
    ~RpcClient();
    void CallMethod(const MethodDescriptor* method,
		            RpcController* controller, 
                    const Message* request,
		            Message* response, 
                    Closure* done);

private:
    void onConnection(const TcpConnectionPtr &);
	void onMessage(const TcpConnectionPtr&, Buffer*, TimeStamp);

    EventLoop _loop;
    TcpClient _cli;

    std::function<void(const TcpConnectionPtr &)> _send;
	std::function<void(const std::string &)> _parse_rsp;
};

#endif // RPC_CLIENT_H