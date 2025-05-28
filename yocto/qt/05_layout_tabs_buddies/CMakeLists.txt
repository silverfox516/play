include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(layout_tabs_buddies src/main.cpp src/dialog.cpp)
install(TARGETS layout_tabs_buddies RUNTIME DESTINATION bin)

