set(RPC_PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc.proto
    # ${CMAKE_CURRENT_SOURCE_DIR}/rpcservice.proto
)
# message(${RPC_PROTOS})
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR} ${RPC_PROTOS})
# message(${PROTOBUF_PROTOC_EXECUTABLE})
# add_custom_command( OUTPUT rpc.pb.h rpc.pb.cc rpcservice.pb.h rpcservicepb.cc
#                     COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} #protoc
#                     ARGS --cpp_out=. RPC_PROTOS -I ${CMAKE_CURRENT_SOURCE_DIR}
#                     DEPENDS ${RPC_PROTOS}
# )
EXEC_PROGRAM(${PROTOBUF_PROTOC_EXECUTABLE} 
             ARGS --cpp_out=${CMAKE_CURRENT_SOURCE_DIR} ${RPC_PROTOS} -I${CMAKE_CURRENT_SOURCE_DIR})

set(rpc_SRCS
    RpcFrame.cpp
    RpcCoder.cpp
    rpc.pb.cc
    TcpServer.cpp
    ConnectionQueue.cpp
    LocalConfig.cpp
)

add_library(RPC ${rpc_SRCS})
target_link_libraries(RPC tinyxml protobuf Net)

add_subdirectory(tests)