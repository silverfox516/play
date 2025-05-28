include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(displaying_windows src/main.cpp src/main_window.cpp src/my_dialog.cpp)
install(TARGETS displaying_windows RUNTIME DESTINATION bin)

