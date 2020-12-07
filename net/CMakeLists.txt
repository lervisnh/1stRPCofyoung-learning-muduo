set(net_SRCS
    Acceptor.cpp
    Buffer.cpp
    Channel.cpp
    TcpServer.cpp
    EventLoopThreadPool.cpp
    EventLoopThread.cpp
    EventLoop.cpp
    InetAddress.cpp
    Poller.cpp
    Epoll.cpp
    Socket.cpp
    SocketOps.cpp
    TcpConnection.cpp
    Timer.cpp
    TimerQueue.cpp
    CurrentThread.cpp
)

add_library(Net ${net_SRCS})
target_link_libraries(Net Base)

add_subdirectory(tests)