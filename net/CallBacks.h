#ifndef NET_CALLBACKS_H
#define NET_CALLBACKS_H

#include <functional>
#include <memory>

#include "base/TimeStamp.h"

class Buffer;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

namespace NetCallBacks
{

// All client visible callbacks go here.

typedef std::function<void ()> TimerCallBack;
typedef std::function<void (const TcpConnectionPtr& )> ConnectionCallBack;
typedef std::function<void (const TcpConnectionPtr& , Buffer*, TimeStamp)> MessageCallBack;
typedef std::function<void (const TcpConnectionPtr& )> CloseCallBack;
typedef std::function<void (const TcpConnectionPtr& )> WriteCompleteCallback;
typedef std::function<void (const TcpConnectionPtr&, size_t )> HighWaterMarkCallback;

void defaultConnectionCallBack(const TcpConnectionPtr&);
void defaultMessageCallBack(const TcpConnectionPtr&, Buffer*, TimeStamp);

}
#endif  // NET_CALLBACKS_H
