#include "echo_tcpserver.h"

#include "base/Logger.h"
#include "net/EventLoop.h"

#include <unistd.h>

// using namespace muduo;
// using namespace muduo::net;

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        LOG_INFO << "pid = " << getpid();
        Logger::setLogLevel(Logger::TRACE);
        EventLoop loop;
        InetAddress listenAddr(atoi(argv[1]));
        EchoServer server(&loop, listenAddr);
        server.start();
        loop.loop();
    }
    else
    {
        printf("Usage: %s port\n", argv[0]);
    }
}

