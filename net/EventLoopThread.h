#ifndef NET_EVENTLOOPTHREAD_H
#define NET_EVENTLOOPTHREAD_H

#include <functional>
#include <mutex>

#include "base/Condition.h"
#include "base/Thread.h"

class EventLoop;

class EventLoopThread{
public:
  typedef std::function<void(EventLoop* )> ThreadInitCallBack;

  // EventLoopThread();
  EventLoopThread(const ThreadInitCallBack& cb = ThreadInitCallBack());
  ~EventLoopThread();

  EventLoop* startLoop();

private:
  const EventLoopThread& operator=(const EventLoopThread&);
  EventLoopThread(const EventLoopThread&);

  void threadFunc();

  EventLoop* p_loop;
  bool m_exiting;
  Thread m_thread;
  std::mutex m_mutex;
  Condition m_cond;
  ThreadInitCallBack m_threadInitCallBack;

};

#endif