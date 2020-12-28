cmake_minimum_required (VERSION 2.8)
project(sharpRPC)

add_definitions(-std=c++11)
# set(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(${PROJECT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
find_package(Protobuf REQUIRED)

add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(rpc)
add_subdirectory(submodules/tinyxml)
