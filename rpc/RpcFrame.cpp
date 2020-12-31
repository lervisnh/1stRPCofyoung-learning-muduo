
#include "rpc/RpcFrame.h"
#include "rpc/RpcCoder.h"
#include "base/Logger.h"
#include <assert.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>

static ConnectionQueue g_toWorkersQueue;
static ConnectionQueue g_fromWorkersQueue;

namespace RpcCallBacks {
    void defaultConnectionCallBack(const TcpConnectionPtr& conn){
        NetCallBacks::defaultConnectionCallBack(conn);
        // LOG_TRACE << "defaultConnectionCallBack enqueue finished. ";
    };
    void defaultMessageCallBack(const TcpConnectionPtr& conn, 
                                            Buffer* buf, 
                                            TimeStamp receiveTime)
    {
        LOG_TRACE << " Connection " << conn->name() << " : "
                << " readable buf has " << buf->readableBytes() << "Bytes , "
                << " writable buf has " << buf->writableBytes() << "Bytes ";
                //   << " at " << receiveTime.toString();
        g_toWorkersQueue.enqueue(conn->shared_from_this());
    };
} // namespace RpcCallBacks

// ###########################################################################

RpcFrame::RpcFrame(EventLoop* listenLoop, TcpServer* toWorkersIO) :
                        _running(false),
                        _toMeQueue(&g_toWorkersQueue),
                        _fromMeQueue(&g_fromWorkersQueue),
                        _listenLoop(listenLoop),
                        _toMeIO(toWorkersIO),
                        _threadNums(0)
{
    _toMeIO->setConnectionCallback(RpcCallBacks::defaultConnectionCallBack);
    _toMeIO->setMessageCallback(RpcCallBacks::defaultMessageCallBack);
};

RpcFrame::~RpcFrame(){
    _running = false;
    _pool.stop();
};

void RpcFrame::setWorkers(int threadNum){
    assert(_threadNums==0);
    _threadNums = threadNum;
    LOG_TRACE << _threadNums << " workers";
}

void RpcFrame::start(){
    assert(_running == false);
    _running = true;

    _pool.setThreadInitCallback(std::bind(&RpcFrame::workerLoop, this));
    _pool.setMaxQueueSize(50);
    _pool.start(_threadNums);

    _toMeIO->start();
    _listenLoop->loop();
}

void RpcFrame::registerService(google::protobuf::Service* s){
    const google::protobuf::ServiceDescriptor* desc = s->GetDescriptor();
    std::string srv_name (desc->full_name());
    LOG_INFO << "Register Service : " << srv_name;
    _services[srv_name] = s;
}


void RpcFrame::workerLoop(){
    LOG_TRACE << "Worker thread: " << CurrentThread::tid() << " starting ... ";
    while (_running)
    {
        TcpConnectionPtr conn;
        _toMeQueue->waitDequeue(conn);

        RpcCoder inputCodec(conn->getInputBuffer());
        if (!(inputCodec.unpack())){
            LOG_ERROR << "Connection: " << conn->name() << ", input buffer unpack failed";
            continue;
        }
        RpcMessagePtr& inputMsg = inputCodec.getRpcMessage();
        
        // 解析service
        std::map<std::string, google::protobuf::Service*>::const_iterator 
                              iter = _services.find(inputMsg->service());
        if (iter == _services.end()) // no service
        {
            // TODO : ADD
            LOG_ERROR << "Connection: " << conn->name() << ", no service: " << inputMsg->service();
            continue ;
        }
        google::protobuf::Service* service = iter->second;
        assert(service != NULL);

        // 解析method
        const google::protobuf::ServiceDescriptor* desc = service->GetDescriptor();
        const google::protobuf::MethodDescriptor* method
          = desc->FindMethodByName(inputMsg->method());
        
        if (method == NULL)// no method
        {
            // TODO : ADD
            LOG_ERROR << "Connection: " << conn->name() << ", no method: " << inputMsg->method();
            continue ;
        }
        
        // TODO : 根据MessageType识别是请求还是应答，为向下游发起服务准备
        //（此处参考了muduo）
        RPCServices::MessageType msgType =  inputMsg->type();

        // 解析 请求 和 应答
        std::unique_ptr<google::protobuf::Message> req(service->GetRequestPrototype(method).New());
        if (!(req->ParseFromString(inputMsg->request())))
        { // request parse fail
            // TODO : ADD
            LOG_ERROR << "Connection: " << conn->name() << ", request parse failed";
            continue ;
        }
        google::protobuf::Message* rsp = service->GetResponsePrototype(method).New();
        // 调用函数
        service->CallMethod(method, NULL, req.get(), rsp, NULL);

        // 序列化应答
        RpcCoder outputCodec(conn->getOutputBuffer());
        if (!(outputCodec.pack(rsp)))
        { // response pack fail
            // TODO : ADD
            LOG_ERROR << "Connection: " << conn->name() << ", response pack failed";
            continue ;
        }

        // 发送应答
        conn->send(conn->getOutputBuffer());
    }
}


