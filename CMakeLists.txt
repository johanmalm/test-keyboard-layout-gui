cmake_minimum_required(VERSION 3.23)
project(layout LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(layout
    main.cpp
    window.cpp window.h
    layoutmodel.cpp layoutmodel.h
    evdev-lst-layouts.h
)

target_link_libraries(layout PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
