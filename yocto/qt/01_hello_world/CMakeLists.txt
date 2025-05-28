include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(hello_world src/main.cpp)
install(TARGETS hello_world RUNTIME DESTINATION bin)

