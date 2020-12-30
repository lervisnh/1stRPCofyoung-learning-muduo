#include "rpc/TcpClient.h"

#include "base/Logger.h"
#include "base/Thread.h"
#include "net/EventLoop.h"
#include "net/InetAddress.h"

#include <utility>

#include <stdio.h>
#include <unistd.h>
#include <string>

using namespace std::placeholders;

class EchoClient
{
 public:
  EchoClient(EventLoop* loop, const InetAddress& listenAddr, int size)
    : loop_(loop),
      client_(loop, listenAddr, "EchoClient"),
      msg(size, '4')
  {
    client_.setConnectionCallback(
        std::bind(&EchoClient::onConnection, this, _1));
    client_.setMessageCallback(
        std::bind(&EchoClient::onMessage, this, _1, _2, _3));
    //client_.enableRetry();
  }

  void connect()
  {
    client_.connect();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    LOG_TRACE << conn->localAddress().toIpPort() << " -> "
        << conn->peerAddress().toIpPort() << " is "
        << (conn->isConnected() ? "UP" : "DOWN");

    if (conn->isConnected())
    {
      conn->setTcpNoDelay(true);
      conn->send(msg);
    }
    else
    {
      loop_->quit();
    }
  }

  void onMessage(const TcpConnectionPtr& conn, Buffer* buf, TimeStamp time)
  {
    LOG_INFO << conn->name() << " send : " << buf->peek();
    conn->send(buf);
  }

  EventLoop* loop_;
  TcpClient client_;
  std::string msg;
};

int main(int argc, char* argv[])
{
  Logger::setLogLevel(Logger::INFO);
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  if (argc < 3){
    printf("Usage: %s host_ip port ( msg_size[default=256] )\n", argv[0]);
  }
    
  int port = atoi(argv[2]);
  int size = argc<4 ? 256 : atoi(argv[3]);
  EventLoop loop;
  InetAddress serverAddr(argv[1], port);
  EchoClient client(&loop, serverAddr, size);
  client.connect();
  loop.loop();
}

