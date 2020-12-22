add_executable(localconfig_test LocalConfig_test.cc)
target_link_libraries(localconfig_test RPC)

add_executable(echo_tcpserver echo_tcpserver/echo_tcpserver.cc echo_tcpserver/main.cc)
target_link_libraries(echo_tcpserver RPC)

add_executable(rpc_frame_test RpcFrame_test.cc)
target_link_libraries(rpc_frame_test RPC)

add_subdirectory(rpc_service)