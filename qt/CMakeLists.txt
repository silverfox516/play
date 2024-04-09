cmake_minimum_required(VERSION 3.5)

project(qt_example VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
link_libraries(${Qt5Widgets_LIBRARIES})

add_subdirectory(dialog1)
add_subdirectory(01_hello_world)
add_subdirectory(02_gui_programming)
add_subdirectory(03_signal_and_slots)
add_subdirectory(04_displaying_windows)
add_subdirectory(05_layout_tabs_buddies)
