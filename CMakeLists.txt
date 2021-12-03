cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

PROJECT(NETWORK)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(udpcliserv)
add_subdirectory(inetd)
add_subdirectory(unixdomain)
add_subdirectory(nonblock)
