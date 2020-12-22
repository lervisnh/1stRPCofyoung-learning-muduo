#include "ConnectionQueue.h"
#include "base/CurrentThread.h"
#include "base/Logger.h"

// ConnectionQueue::ConnectionQueue(){};
// ConnectionQueue::~ConnectionQueue(){};

bool ConnectionQueue::enqueue(const TcpConnectionPtr& conn){
    if (_mq.enqueue(conn)) // enqueue success
    {
        LOG_TRACE << conn->name() << " enqueue success ";
        return true;
    } else
    {
        LOG_ERROR << conn->name() << " enqueue failed ";
        return false;
    }
}

void ConnectionQueue::waitDequeue(TcpConnectionPtr& conn){
    _mq.wait_dequeue(conn);
    LOG_TRACE << conn->name() << " is dequeued by worker thread " << CurrentThread::tid();
}
