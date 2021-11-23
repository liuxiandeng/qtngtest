cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(ssltest)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SSLTEST_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    sslhelper.h
    sslhelper.cpp
)
    
    

add_subdirectory(qtnetworkng)
add_executable(ssltest ${SSLTEST_SOURCES})

target_link_libraries(ssltest PRIVATE Qt5::Widgets qtnetworkng)
