cmake_minimum_required (VERSION 2.6)


project (lcd)

message ("Build lcd library")

set (HEADER_FILES
    nokia_1202.h)

set (SOURCE_FILES
    nokia_1202.c)

add_library (lcd ${HEADER_FILES} ${SOURCE_FILES})

set (LCD_LIBRARY lcd CACHE PATH "lcd library available")
