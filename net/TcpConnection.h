#ifndef NET_TCPCONNECTION_H
#define NET_TCPCONNECTION_H

#include <memory>
#include <string>

#include "InetAddress.h"
#include "Socket.h"
#include "CallBacks.h"
#include "Channel.h"
#include "Buffer.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection> 
{
public:
  TcpConnection(EventLoop* loop,
                const std::string& name,
                int sockfd,
                const InetAddress& localAddr,
                const InetAddress& peerAddr);
  ~TcpConnection();

  EventLoop* getLoop() const { return p_loop; }
  const std::string& name() const { return m_name; }
  const InetAddress& localAddress() const { return m_localAddr; }
  const InetAddress& peerAddress() const { return m_peerAddr; }
  void setConnectionCallBack(const NetCallBacks::ConnectionCallBack& cb) 
  { m_connectionCallBack = cb; }
  void setMessageCallBack(const NetCallBacks::MessageCallBack& cb) 
  { m_messageCallBack = cb; }
  void setCloseCallBack(const NetCallBacks::CloseCallBack& cb) 
  { m_closeCallBack = cb; }

  void setWriteCompleteCallback(const NetCallBacks::WriteCompleteCallback& cb)
  { m_writeCompleteCallBack = cb; }
  void setHighWaterMarkCallback(const NetCallBacks::HighWaterMarkCallback& cb, size_t highWaterMark)
  { m_highWaterMarkCallback = cb; highWaterMark = highWaterMark; }

  Buffer* getInputBuffer() {return &m_inputBuffer;}
  Buffer* getOutputBuffer() {return &m_outputBuffer;}

  // called when TcpServer accepts a new connection
  void connectEstablished();   // should be called only once
  // called when TcpServer has removed me from its map
  void connectDestroyed();  // should be called only once

  // void send(string&& message); // C++11
  void send(const void* message, size_t len); // TODO : modified
  void send(const std::string& message); // TODO : modified
  // void send(Buffer&& message); // C++11
  void send(Buffer* message);  // this one will swap data // TODO : modified

  void shutdown();
  void forceClose();

  bool isConnected() const { return m_state == kConnected; }
  bool isDisConnected() const { return m_state == kDisConnected; }
  const char* stateToString() const;

private:
  enum StateE { kDisConnected, kConnecting, kDisConnecting, kConnected, };

  void setState(StateE s) { m_state = s; }
  void handleRead();
  void handleWrite();
  void handleError();
  void handleClose();
  void sendInLoop(const void* data, size_t len);
  void shutdownInLoop();
  void forceCloseInLoop();

  EventLoop* p_loop;
  std::string m_name;
  StateE m_state;
  std::unique_ptr<Socket> p_socket;
  std::unique_ptr<Channel> p_channel;
  InetAddress m_localAddr;
  InetAddress m_peerAddr;

  NetCallBacks::ConnectionCallBack m_connectionCallBack;
  NetCallBacks::MessageCallBack m_messageCallBack;
  NetCallBacks::CloseCallBack m_closeCallBack;
  NetCallBacks::WriteCompleteCallback m_writeCompleteCallBack;
  NetCallBacks::HighWaterMarkCallback m_highWaterMarkCallback;

  size_t highWaterMark;

  Buffer m_inputBuffer;
  Buffer m_outputBuffer;
};

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

#endif