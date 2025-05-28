include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(gui_programming src/main.cpp src/main_window.cpp)
install(TARGETS gui_programming RUNTIME DESTINATION bin)

