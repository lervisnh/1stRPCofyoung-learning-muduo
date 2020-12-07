add_executable(buffer_test Buffer_test.cc)
target_link_libraries(buffer_test Net)

add_executable(simple_echo echo/echo.cc echo/main.cc)
target_link_libraries(simple_echo Net)