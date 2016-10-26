include_directories('.')

find_package(Threads)

add_executable(snake-server main.cpp ..)

target_link_libraries(snake-server ${CMAKE_THREAD_LIBS_INIT})
