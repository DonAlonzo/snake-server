cmake_minimum_required(VERSION 2.8)
project(snake-server)

include_directories(external/websocketpp)
include_directories(external/asio/asio/include)

add_subdirectory(src)
