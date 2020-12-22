
#include "net/EventLoop.h"
#include "base/ThreadPool.h"
#include "ConnectionQueue.h"
#include "rpc/TcpServer.h"

// #include "rpcservice.pb.h"

#include <map>
#include <string>

namespace google{
namespace protobuf{
    class Service;
    class MethodDescriptor;
}
}


class RpcFrame
{
public:
    RpcFrame(EventLoop*, TcpServer*);
    ~RpcFrame();

    void setWorkers(int);

    void start();

    void registerService(google::protobuf::Service*);

private:
    ThreadPool _pool;
    TcpServer* _toMeIO;
    EventLoop* _listenLoop;

    int _threadNums;
    volatile bool _running;

    ConnectionQueue* _toMeQueue;
    ConnectionQueue* _fromMeQueue;

    std::map<std::string, ::google::protobuf::Service*> _services;

    // void _startIO();
    void workerLoop();
};