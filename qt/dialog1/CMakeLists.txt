include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(dialog1 src/main.cpp src/eg_dialog.cpp src/eg_dialog.h)
install(TARGETS dialog1 RUNTIME DESTINATION bin)
