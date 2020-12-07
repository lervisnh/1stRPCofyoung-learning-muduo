set(rpc_SRCS
    LocalConfig.cpp
)

add_library(RPC ${rpc_SRCS})
target_link_libraries(RPC tinyxml Base)

add_subdirectory(tests)