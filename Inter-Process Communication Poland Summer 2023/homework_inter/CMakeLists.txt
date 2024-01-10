cmake_minimum_required(VERSION 3.10)

project(FileTransferApp)

# Ensure C++11 features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for any header files
#include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable targets
add_executable(server server.cpp)
add_executable(client client.cpp)

# Link any libraries if necessary
# For example, to link against the Threads library:
# find_package(Threads)
# target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
# target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})
