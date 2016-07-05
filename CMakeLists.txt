cmake_minimum_required(VERSION 3.5)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES event.cpp event_loop.h event_loop.cpp io_file.h logger.h buffer.h epoll_event_loop.h ae_handler.h socket_utils.h socket_utils.cpp)
add_executable(server ${SOURCE_FILES})