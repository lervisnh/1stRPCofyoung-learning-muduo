
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
    // TODO : simplify codings
    const int32_t len = _buf->peekInt32();
    if (_buf->readableBytes() >= implicit_cast<size_t>(kHeaderLen+len))
    {
        const char* data = _buf->peek() + kHeaderLen;
        int32_t data_len = len;// - kHeaderLen;
        
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

    // TODO : simplify codings
    std::string bufStr = _rpcMsg->SerializeAsString();
    // if (buf.size()<1)
    // {
    //     // LOG_ERROR << "Conn " << _conn->name() << ": input buffer error";
        
    // }
    

    _buf->append(bufStr.data(), bufStr.size());

    int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(_buf->readableBytes()));
    _buf->prepend(&len, sizeof(len));

    return true;
};

void RpcCoder::unpack(Buffer* buf, RpcMessage& msg)
{
    const int32_t len = buf->peekInt32();
    if (buf->readableBytes() >= implicit_cast<size_t>(implicit_cast<size_t>(kHeaderLen+len)))
    {
        const char* data = buf->peek() + kHeaderLen;
        int32_t data_len = len;// - kHeaderLen;
        
        if (!(msg.ParseFromString(std::string(data, data_len)))){
            LOG_DEBUG << "RPC message parse error";
        }
        buf->retrieve(kHeaderLen+len);
        return ;
    }

    LOG_DEBUG << "input buffer error";
    return ;
};

void RpcCoder::pack(Buffer* buf, RpcMessage& msg)
{
    std::string bufStr = msg.SerializeAsString();
    buf->append(bufStr.data(), bufStr.size());

    int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(buf->readableBytes()));
    buf->prepend(&len, sizeof(len));
};