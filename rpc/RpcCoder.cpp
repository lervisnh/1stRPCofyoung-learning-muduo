
#include "rpc/RpcCoder.h"
#include "base/Logger.h"
#include <assert.h>

template<typename To, typename From>
inline To implicit_cast(From const &f)
{
  return f;
}

RpcCoder::RpcCoder(Buffer* buf) : 
    _buf(buf),
    _rpcMsg(new RpcMessage)
{
};

RpcCoder::~RpcCoder()
{
};


bool RpcCoder::unpack(){
    const int32_t len = _buf->peekInt32();
    if (_buf->readableBytes() >= implicit_cast<size_t>(kHeaderLen+len))
    {
        const char* data = _buf->peek() + kHeaderLen;
        int32_t data_len = len - kHeaderLen;
        
        if (!(_rpcMsg->ParseFromString(std::string(data, data_len)))){
            LOG_DEBUG << "RPC message parse error";
            return false;
        }
        _buf->retrieve(kHeaderLen+len);
        return true;
    }

    LOG_DEBUG << "input buffer error";
    return false;
};

bool RpcCoder::pack(google::protobuf::Message* rsp){
    _rpcMsg->set_type(RPCServices::RESPONSE);
    _rpcMsg->set_response(rsp->SerializeAsString());

    std::string buf = _rpcMsg->SerializeAsString();

    // if (buf.size()<1)
    // {
    //     // LOG_ERROR << "Conn " << _conn->name() << ": input buffer error";
        
    // }
    

    _buf->append(buf.data(), buf.size());

    int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(_buf->readableBytes()));
    _buf->prepend(&len, sizeof(len));

    return true;
};
