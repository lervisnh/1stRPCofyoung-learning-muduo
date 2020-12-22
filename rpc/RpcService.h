
#include "rpc/LocalConfig.h"
#include "rpc/RpcFrame.h"

class RpcService
{
public:
    explicit RpcService(const char*);
    ~RpcService();

    void registerService(google::protobuf::Service*);
    void start();

private:
    LocalConfig* _configFile;

    std::unique_ptr<EventLoop> _listenLoop;
    std::unique_ptr<InetAddress> _listenAddr;
    std::unique_ptr<TcpServer> g_toWorkersIO;

    std::unique_ptr<RpcFrame> _rpcFrame;
};

RpcService::RpcService(const char* configFile)
{
    assert(_configFile->SetConfigFile(configFile)==true);
    _configFile = _configFile->GetInstance();

    Logger::setLogLevel(_configFile->GetServerLogLevel());
    std::string ip = _configFile->GetServerIp();
    uint16_t port = _configFile->GetServerPort();

    _listenLoop.reset(new EventLoop);
    _listenAddr.reset(new InetAddress(ip, port));
    g_toWorkersIO.reset(new TcpServer(_listenLoop.get(),
                                      (*_listenAddr.get()),
                                      "reactor_in_io"));
    
    _rpcFrame.reset(new RpcFrame(_listenLoop.get(), g_toWorkersIO.get()));
}

RpcService::~RpcService()
{
}

void RpcService::registerService(google::protobuf::Service* s){
    _rpcFrame->registerService(s);
}

void RpcService::start(){
    _rpcFrame->setWorkers(_configFile->GetServerWorkers());
    _rpcFrame->start();
}