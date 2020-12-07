set(base_SRCS
    AsyncLogging.cpp
    FileUtil.cpp
    LogFile.cpp
    Logger.cpp
    LogStream.cpp
    TimeStamp.cpp
    Thread.cpp
  )

add_library(Base ${base_SRCS})
target_link_libraries(Base rt)

add_subdirectory(tests)