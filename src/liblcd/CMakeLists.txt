cmake_minimum_required (VERSION 2.6)

include (${BASE_DIRECTORY}/winavr.cmake)
include (${BASE_DIRECTORY}/settings.cmake)

project (lcd)

message ("Build lcd library\n")

set (HEADER_FILES
    include/font.h
    include/font_15x24.h
    include/font_15x24_5.h
    include/nokia_1202.h)

set (SOURCE_FILES
    src/nokia_1202.c)

add_library (lcd ${HEADER_FILES} ${SOURCE_FILES})

set (LCD_LIBRARY lcd CACHE PATH "lcd library available")
