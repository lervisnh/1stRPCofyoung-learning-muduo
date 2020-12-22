#include "echo_tcpserver.h"

#include "base/Logger.h"
#include <string>

// using namespace muduo;
// using namespace muduo::net;

EchoServer::EchoServer(EventLoop* loop,
                       const InetAddress& listenAddr)
  : server_(loop, listenAddr, "EchoServer")
{
  server_.setMessageCallback(
      std::bind(&EchoServer::onMessage, this, 
                std::placeholders::_1, 
                std::placeholders::_2, 
                std::placeholders::_3));
}

void EchoServer::start()
{
  server_.setThreadNum(3);
  server_.start();
}

void EchoServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           TimeStamp time)
{
  std::string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
           << "data received at " << time.toString();
  conn->send(msg);
}