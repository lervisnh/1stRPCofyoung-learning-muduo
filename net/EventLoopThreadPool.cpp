
#include "EventLoopThreadPool.h"

#include "EventLoop.h"
#include "EventLoopThread.h"

#include <stdio.h>
#include <iostream>

template<typename To, typename From>
inline To implicit_cast(From const &f)
{ return f; }

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg)
  : p_baseLoop(baseLoop),
    m_name(nameArg),
    m_started(false),
    m_numThreads(0),
    m_next(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
  // Don't delete loop, it's stack variable
}

void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
  assert(!m_started);
  p_baseLoop->assertInLoopThread();

  m_started = true;

  for (int i = 0; i < m_numThreads; ++i)
  {
    char buf[m_name.size() + 32];
    snprintf(buf, sizeof buf, "%s%d", m_name.c_str(), i);
    EventLoopThread* t = new EventLoopThread(cb);
    m_eventLoopThreads.push_back(std::unique_ptr<EventLoopThread>(t));
    m_eventLoops.push_back(t->startLoop());
  }
  if (m_numThreads == 0 && cb)
  {
    cb(p_baseLoop);
  }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
  p_baseLoop->assertInLoopThread();
  assert(m_started);
  EventLoop* loop = p_baseLoop;

  if (!m_eventLoops.empty())
  {
    // round-robin
    loop = m_eventLoops[m_next];
    ++m_next;
    if (implicit_cast<size_t>(m_next) >= m_eventLoops.size())
    {
      m_next = 0;
    }
  }
  return loop;
}

EventLoop* EventLoopThreadPool::getLoopForHash(size_t hashCode)
{
  p_baseLoop->assertInLoopThread();
  EventLoop* loop = p_baseLoop;

  if (!m_eventLoops.empty())
  {
    loop = m_eventLoops[hashCode % m_eventLoops.size()];
  }
  return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
  p_baseLoop->assertInLoopThread();
  assert(m_started);
  if (m_eventLoops.empty())
  {
    return std::vector<EventLoop*>(1, p_baseLoop);
  }
  else
  {
    return m_eventLoops;
  }
}
