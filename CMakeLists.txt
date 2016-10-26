cmake_minimum_required(VERSION 3.1)
project(snake-server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

include_directories(external/websocketpp)
include_directories(external/asio/asio/include)

add_subdirectory(src)
