cmake_minimum_required(VERSION 3.21.1)

project(homeworkApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

add_executable(homeworkApp
    main.cpp


    src/main.qml

    ImageFetcher.h
    ImageFetcher.cpp

)

target_link_libraries(homeworkApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS homeworkApp
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
