
#include "base/Logger.h"
#include "rpc/RpcClient.h"
#include "rpc/rpc.pb.h"
#include "rpc/RpcCoder.h"

#include <functional>
#include <string>

using namespace RPCServices;
using namespace std::placeholders;

RpcClient::RpcClient(const InetAddress& serverAddr)
                    : _cli(&_loop, serverAddr, "RpcClient")
{
    _cli.setConnectionCallback(std::bind(&RpcClient::onConnection, this, _1));
    _cli.setMessageCallback(std::bind(&RpcClient::onMessage, this, _1, _2, _3));
};

RpcClient::~RpcClient()
{
};

void RpcClient::CallMethod( const MethodDescriptor* method,
                            RpcController* controller, 
                            const Message* request,
                            Message* response,
                            Closure* done)
{
    const google::protobuf::ServiceDescriptor* srv  = method->service();
    std::string srv_name (srv->full_name());
    std::string mthd_name (method->name());

    RpcMessage msg;
    msg.set_type(MessageType::REQUEST);
    msg.set_service(srv_name);
    msg.set_method(mthd_name);
    msg.set_request(request->SerializeAsString());
    
    std::string send_msg (msg.SerializeAsString());
    int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(send_msg.size()));
    send_msg.insert(0, std::string((char*)&len, sizeof(len)));

    _send = [&](const TcpConnectionPtr & conn)
                    { conn->send(send_msg); };
    _parse_rsp = [&](const std::string & str)
                    { response->ParseFromString(str);  };

    _cli.connect();
    _loop.loop();
};

// 处理新的连接和关闭连接
void RpcClient::onConnection(const TcpConnectionPtr & conn)
{
	if (conn->isConnected()) // 连接上服务器
	{
		// 发送数据、使用回调函数
		// 因为发送的数据在callmethod
        LOG_INFO << "Connection " << conn->name()
                 << " send " << conn->getOutputBuffer()->peek();
        _send(conn);
	}
	else // 断开服务
	{
		conn->shutdown(); // 关闭连接
        _loop.quit();
	}
};

// 处理收发数据
void RpcClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf, TimeStamp time)
{
	RpcMessage msg;
    RpcCoder::unpack(buf, msg);
	if (msg.type()==MessageType::RESPONSE)
    {
        _parse_rsp(msg.response());
    }
    conn->shutdown();
};