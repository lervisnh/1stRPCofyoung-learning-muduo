#ifndef NET_TCPCLIENT_H
#define NET_TCPCLIENT_H

#include "net/TcpConnection.h"
#include <mutex>
#include <string>


class Connector;
typedef std::shared_ptr<Connector> ConnectorPtr;

class TcpClient
{
 public:
  // TcpClient(EventLoop* loop);
  // TcpClient(EventLoop* loop, const string& host, uint16_t port);
  TcpClient(EventLoop* loop,
            const InetAddress& serverAddr,
            const std::string& nameArg);
  ~TcpClient();  // force out-line dtor, for std::unique_ptr members.

  void connect();
  void disconnect();
  void stop();

  TcpConnectionPtr connection() const
  {
    std::lock_guard<std::mutex> lock(mutex_);
    return connection_;
  }

  EventLoop* getLoop() const { return loop_; }
  bool retry() const { return retry_; }
  void enableRetry() { retry_ = true; }

  const std::string& name() const
  { return name_; }

  /// Set connection callback.
  /// Not thread safe.
  void setConnectionCallback(NetCallBacks::ConnectionCallBack cb)
  { connectionCallback_ = std::move(cb); }

  /// Set message callback.
  /// Not thread safe.
  void setMessageCallback(NetCallBacks::MessageCallBack cb)
  { messageCallback_ = std::move(cb); }

  /// Set write complete callback.
  /// Not thread safe.
  void setWriteCompleteCallback(NetCallBacks::WriteCompleteCallback cb)
  { writeCompleteCallback_ = std::move(cb); }

 private:
  TcpClient(const TcpClient&);  //禁止复制拷贝
  const TcpClient& operator=(const TcpClient&);
  /// Not thread safe, but in loop
  void newConnection(int sockfd);
  /// Not thread safe, but in loop
  void removeConnection(const TcpConnectionPtr& conn);

  EventLoop* loop_;
  ConnectorPtr connector_; // avoid revealing Connector
  const std::string name_;
  NetCallBacks::ConnectionCallBack connectionCallback_;
  NetCallBacks::MessageCallBack messageCallback_;
  NetCallBacks::WriteCompleteCallback writeCompleteCallback_;
  bool retry_;   // atomic
  bool connect_; // atomic
  // always in loop thread
  int nextConnId_;
  mutable std::mutex mutex_;
  TcpConnectionPtr connection_ ;
};


#endif  // NET_TCPCLIENT_H
