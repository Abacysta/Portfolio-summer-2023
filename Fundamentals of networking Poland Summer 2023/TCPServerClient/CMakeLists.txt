cmake_minimum_required(VERSION 3.10)

project(TCPServerClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(TCPServerClient src/main.cpp)

target_link_libraries(TCPServerClient Threads::Threads)
