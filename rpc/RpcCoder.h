
// #include "net/TcpConnection.h"
// #include "rpc/RpcFrame.h"
#include "net/Buffer.h"
#include "rpc/rpc.pb.h"
// #include <string>
#include <memory>

using RPCServices::RpcMessage;
typedef std::shared_ptr<RpcMessage> RpcMessagePtr;

class RpcCoder
{
public:
    const static int32_t kHeaderLen = sizeof(int32_t);

    explicit RpcCoder(Buffer*);
    ~RpcCoder();

    bool unpack();
    bool pack(google::protobuf::Message* rsp);

    // std::string getRequest();
    // std::string getResponse();
    RpcMessagePtr& getRpcMessage(){
        return _rpcMsg;
    };

    static void unpack(Buffer*, RpcMessage&);
    static void pack(Buffer*, RpcMessage&);

private:
    /* data */
    Buffer* _buf;
    RpcMessagePtr _rpcMsg;
};