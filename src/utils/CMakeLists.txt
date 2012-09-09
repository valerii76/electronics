cmake_minimum_required (VERSION 2.6)

project (utils)

message ("Build utils library")

set (HEADER_FILES
    dbg_flash.h)

set (SOURCE_FILES
    dbg_uart.c)

add_library (utils ${HEADER_FILES} ${SOURCE_FILES})

set (UTILS_LIBRARY utils CACHE PATH "utils library available")
