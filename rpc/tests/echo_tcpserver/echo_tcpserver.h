#ifndef EXAMPLES_SIMPLE_ECHO_ECHO_H
#define EXAMPLES_SIMPLE_ECHO_ECHO_H

#include "rpc/TcpServer.h"

// RFC 862
class EchoServer
{
 public:
  EchoServer(EventLoop* loop,
             const InetAddress& listenAddr);

  void start();  // calls server_.start();

 private:
  TcpServer server_;
  
  // void onConnection(const TcpConnectionPtr& conn);

  void onMessage(const TcpConnectionPtr& conn,
                 Buffer* buf,
                 TimeStamp time);
};

#endif  // MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
