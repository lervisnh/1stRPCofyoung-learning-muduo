set(base_SRCS
    AsyncLogging.cpp
    FileUtil.cpp
    LogFile.cpp
    Logger.cpp
    LogStream.cpp
    TimeStamp.cpp
    ThreadPool.cpp
    Thread.cpp
    CurrentThread.cpp
  )

add_library(Base ${base_SRCS})
target_link_libraries(Base pthread rt)

add_subdirectory(tests)