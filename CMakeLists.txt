cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)
project(timeline)

set(TARGET_NAME ${PROJECT_NAME})

find_package(QT NAMES Qt6 CONFIG REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${TARGET_NAME} main.cpp
    timelineview.h timelineview.cpp
    timelinescene.h
    timelinescene.cpp
    timelineaxis.h
    timelineaxis.cpp
    timelinerow.h
    timelinerow.cpp
)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)