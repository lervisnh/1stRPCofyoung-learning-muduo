#ifndef CONNECTIONQUEUE_H
#define CONNECTIONQUEUE_H

#include "net/TcpConnection.h"

#include "submodules/concurrentqueue/blockingconcurrentqueue.h"
// using namespace moodycamel;

class ConnectionQueue
{
public:
    ConnectionQueue(){};
    ~ConnectionQueue(){};

    bool enqueue(const TcpConnectionPtr&);
    void waitDequeue(TcpConnectionPtr&);

private:
    moodycamel::BlockingConcurrentQueue<TcpConnectionPtr> _mq;
};


#endif 