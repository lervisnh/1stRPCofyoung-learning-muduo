#ifndef EXAMPLES_SIMPLE_ECHO_ECHO_H
#define EXAMPLES_SIMPLE_ECHO_ECHO_H

#include "net/TcpServer.h"

// RFC 862
class EchoServer
{
 public:
  EchoServer(EventLoop* loop,
             const InetAddress& listenAddr);

  void start();  // calls server_.start();

 private:
  TcpServer server_;
};

#endif  // MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
