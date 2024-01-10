cmake_minimum_required(VERSION 3.10)

project(Homework)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/App.cpp
    src/Factory.cpp
    src/FileCollector.cpp
    src/main.cpp
    src/ReportJson.cpp
    src/ReportTxt.cpp
)

find_package(Boost 1.82.0 REQUIRED COMPONENTS json)

add_executable(Homework ${SOURCES})

if(Boost_FOUND)
    target_include_directories(Homework PRIVATE ${Boost_INCLUDE_DIRS} headers)
    target_link_libraries(Homework ${Boost_LIBRARIES})
endif()
