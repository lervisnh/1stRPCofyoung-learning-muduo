#include "echo.h"

#include "base/Logger.h"

// using namespace muduo;
// using namespace muduo::net;

EchoServer::EchoServer(EventLoop* loop,
                       const InetAddress& listenAddr)
  : server_(loop, listenAddr, "EchoServer")
{
}

void EchoServer::start()
{
  server_.setThreadNum(3);
  server_.start();
}

