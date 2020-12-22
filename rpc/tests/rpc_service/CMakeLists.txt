EXEC_PROGRAM(${PROTOBUF_PROTOC_EXECUTABLE} 
             ARGS --cpp_out=${CMAKE_CURRENT_SOURCE_DIR} 
             ${CMAKE_CURRENT_SOURCE_DIR}/echo.proto 
             -I${CMAKE_CURRENT_SOURCE_DIR})
add_executable(rpc_service_test main.cc echo.pb.cc)
target_link_libraries(rpc_service_test RPC)