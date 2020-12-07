#include <assert.h>
#include <poll.h>
#include <signal.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include "EventLoop.h"
#include "Poller.h"
// #include "Poll.h"
#include "Epoll.h"
#include "base/Logger.h"
#include "SocketOps.h"

__thread EventLoop* t_loopInThisThread = 0;

const int kPollTimeMs = 1000;

int createEventfd()
{
  int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

  LOG_TRACE << "createEventfd() fd : " << evtfd;

  if (evtfd < 0)
  {
    LOG_SYSERR << "Failed in eventfd";
    abort();
  }

  return evtfd;
}

EventLoop::EventLoop()
	:m_looping(false),
  m_threadId(CurrentThread::tid()),
  m_poller(new Epoll(this)),
  m_timerQueue(new TimerQueue(this)),
  m_wakeupFd(createEventfd()),
  p_wakeupChannel(new Channel(this, m_wakeupFd)),
  m_callingPendingFunctors(false)
{
  LOG_TRACE << "EventLoop Create " << this << " in thread " << m_threadId;
  if(t_loopInThisThread)
  {  //每个线程只有一个EventLoop对象 , 如果当前线程创建了其他 EventLoop 对象,则终止程序.
    LOG_FATAL << "Anthor EventLoop " << t_loopInThisThread
              << " exists in this thread " << m_threadId;
  }
  else
  {
    t_loopInThisThread = this;
  }
  p_wakeupChannel->setReadCallBack(std::bind(&EventLoop::handleRead, this));
  p_wakeupChannel->enableReading();
}

EventLoop::~EventLoop()
{
  LOG_TRACE << "EventLoop::~EventLoop()";
  assert(!m_looping);
  p_wakeupChannel->disableAll();
  p_wakeupChannel->remove();
  ::close(m_wakeupFd);
  t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
  assert(!m_looping);
  assertInLoopThread();
  m_quit = false;
  m_looping = true;

  LOG_TRACE << "EventLoop " << this << " start loopig";

  while(!m_quit)
  {
    m_activeChannels.clear();
    m_poller->poll(kPollTimeMs, &m_activeChannels);

    printActiveChannels();

    for(ChannelList::iterator it = m_activeChannels.begin();
      it != m_activeChannels.end(); ++it)
    {
      (*it)->handleEvent();
    }
    doPendingFunctors();
  }

  LOG_TRACE << "EventLoop " << this << " stop loopig";
  m_looping = false;

}

bool EventLoop::isInloopThread() const
{
  return m_threadId == CurrentThread::tid();
}

void EventLoop::assertInLoopThread()
{
  if(!isInloopThread())
  {
    abortNotInLoopThread();
  }
}

void EventLoop::runInLoop(const Functor&  cb)
{
  if(isInloopThread())
  {
    cb();
  }
  else
  {
    queueInLoop(cb);
  }
}

void EventLoop::queueInLoop(const Functor& cb)
{
  LOG_TRACE << "EventLoop::queueInLoop()";
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_pendingFunctors.push_back(std::move(cb));
  }

  if(!isInloopThread() || m_callingPendingFunctors)
  {
    wakeup();
  }
}

void EventLoop::wakeup()
{
  uint64_t one = 1;
  ssize_t n = sockets::write(m_wakeupFd, &one, sizeof(one));
  if(n != sizeof(one))
  {
    LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
  }
}

void EventLoop::handleRead() //handle wakeup Fd
{
  LOG_TRACE << "EventLoop::handleRead() handle wakeup Fd";
  uint64_t one = 1;
  ssize_t n = sockets::read(m_wakeupFd, &one, sizeof(one));
  if(n != sizeof(one))
  {
    LOG_ERROR << "EventLoop::handleRead() reads " << n << "bytes instead of 8";
  }
}

void EventLoop::doPendingFunctors()
{
  LOG_TRACE << "EventLoop::doPendingFunctors()";
  std::vector<Functor> functors;
  m_callingPendingFunctors = true;

  {
    std::lock_guard<std::mutex> lock(m_mutex);
    functors.swap(m_pendingFunctors);
  }

  for(size_t i = 0; i < functors.size(); ++i)
  {
    functors[i]();
  }

  m_callingPendingFunctors = false;

}

void EventLoop::abortNotInLoopThread()
{
  LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << m_threadId
            << ", current thread id = " <<  CurrentThread::tid();
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
  return t_loopInThisThread;
}

void EventLoop::quit()
{
  LOG_TRACE << "EventLoop::quit()";
  assert(m_looping == true);

  m_quit = true;

  if(!isInloopThread())
  {
    wakeup();
  }
}

void EventLoop::updateChannel(Channel* channel)
{
  assert(channel->ownerLoop() == this);
  assertInLoopThread();
  m_poller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
  assert(channel->ownerLoop() == this);
  assertInLoopThread();
  if(0)
  {

  }

  m_poller->removeChannel(channel);
}


TimerId EventLoop::runAt(const TimeStamp& time, const NetCallBacks::TimerCallBack& cb)
{
  return m_timerQueue->addTimer(cb, time, 0.0);
}

TimerId EventLoop::runAfter(double delay, const NetCallBacks::TimerCallBack& cb)
{
  TimeStamp time(addTime(TimeStamp::now(), delay));
  return runAt(time, cb);
}

TimerId EventLoop::runEvery(double interval, const NetCallBacks::TimerCallBack& cb)
{
  TimeStamp time(addTime(TimeStamp::now(), interval));
  return m_timerQueue->addTimer(cb, time, interval);
}

void EventLoop::printActiveChannels() const
{
  for (ChannelList::const_iterator it = m_activeChannels.begin();
      it != m_activeChannels.end(); ++it)
  {
    const Channel* ch = *it;
    LOG_TRACE << "{" << ch->reventsToString() << "} ";
  }
}
