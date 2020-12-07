
#ifndef NET_EVENTLOOPTHREADPOOL_H
#define NET_EVENTLOOPTHREADPOOL_H

#include <functional>
#include <memory>
#include <vector>
#include <string>


class EventLoop;
class EventLoopThread;

class EventLoopThreadPool
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg);
  ~EventLoopThreadPool();
  void setThreadNum(int numThreads) { m_numThreads = numThreads; }
  void start(const ThreadInitCallback& cb = ThreadInitCallback());

  // valid after calling start()
  /// round-robin
  EventLoop* getNextLoop();

  /// with the same hash code, it will always return the same EventLoop
  EventLoop* getLoopForHash(size_t hashCode);

  std::vector<EventLoop*> getAllLoops();

  bool started() const
  { return m_started; }

  const std::string& name() const
  { return m_name; }

 private:

  EventLoop* p_baseLoop;
  std::string m_name;
  bool m_started;
  int m_numThreads;
  int m_next;
  std::vector<std::unique_ptr<EventLoopThread>> m_eventLoopThreads;
  std::vector<EventLoop*> m_eventLoops;
};


#endif  // NET_EVENTLOOPTHREADPOOL_H
