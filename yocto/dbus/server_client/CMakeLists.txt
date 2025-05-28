cmake_minimum_required(VERSION 3.5)
project(dbus_example)

function(print_env var)
    message("${${var}}")
endfunction()

find_package(PkgConfig)
pkg_check_modules(DBUS "dbus-1 >= 1.4")
if(DBUS_FOUND)
    include_directories(${DBUS_INCLUDE_DIRS})
    link_libraries(${DBUS_LIBRARIES})
endif()

add_executable(dbus_eg_server src/dbus_eg_server.c)
add_executable(dbus_eg_client src/dbus_eg_client.c)
install(TARGETS dbus_eg_server RUNTIME DESTINATION bin)
install(TARGETS dbus_eg_client RUNTIME DESTINATION bin)
