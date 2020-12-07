#include "Timer.h"

AtomicInt64  Timer::s_numCreated;

void Timer::restart(TimeStamp now)
{
  if(m_repeat)
  {
    m_expiration = addTime(now, m_interval);
  }
  else
  {
    m_expiration = TimeStamp::invalid();
  }

}