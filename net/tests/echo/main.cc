#include "echo.h"

#include "base/Logger.h"
#include "net/EventLoop.h"

#include <unistd.h>

// using namespace muduo;
// using namespace muduo::net;

int main()
{
  LOG_INFO << "pid = " << getpid();
  Logger::setLogLevel(Logger::INFO);
  EventLoop loop;
  InetAddress listenAddr(20007);
  EchoServer server(&loop, listenAddr);
  server.start();
  loop.loop();
}

