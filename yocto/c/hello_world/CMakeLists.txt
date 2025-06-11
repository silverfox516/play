cmake_minimum_required(VERSION 3.5)
project(hello_world)

function(print_env var)
    message("${${var}}")
endfunction()

add_executable(hello_world src/hello_world.c)
install(TARGETS hello_world RUNTIME DESTINATION bin)
