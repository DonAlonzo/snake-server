cmake_minimum_required(VERSION 3.0)
project(snake-server)

include_directories(external/websocketpp)
include_directories(external/asio/asio/include)

add_subdirectory(src)
