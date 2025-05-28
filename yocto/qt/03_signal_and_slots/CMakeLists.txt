include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(signal_and_slots src/main.cpp src/main_window.cpp)
install(TARGETS signal_and_slots RUNTIME DESTINATION bin)

