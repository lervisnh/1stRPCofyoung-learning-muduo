#include "base/ThreadPool.h"
// #include "base/CountDownLatch.h"
#include "base/CurrentThread.h"
#include "base/Logger.h"

#include <stdio.h>
#include <unistd.h>  // usleep

void print()
{
  printf("tid=%d\n", CurrentThread::tid());
}

void printString(const std::string& str)
{
  LOG_INFO << str;
  usleep(100*1000);
}

void longTask(int num);

void test(int maxSize)
{
  LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
  ThreadPool pool("MainThreadPool");
  pool.setMaxQueueSize(maxSize);
  pool.start(5);

  LOG_WARN << "Adding";
  pool.run(print);
  pool.run(print);
  for (int i = 1; i <= 100; ++i)
  {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    pool.run(std::bind(printString, std::string(buf)));
    // pool.run(std::bind(longTask, i));
  }
  LOG_WARN << "Done";

  // muduo::CountDownLatch latch(1);
  // pool.run(std::bind(&muduo::CountDownLatch::countDown, &latch));
  // latch.wait();
  pool.stop();
}


void longTask(int num)
{
  LOG_INFO << "longTask " << num;
  sleep(3);
}

int main()
{
  // test(0);
  // test(1);
  // test(5);
  // test(10);
  test(50);
}
