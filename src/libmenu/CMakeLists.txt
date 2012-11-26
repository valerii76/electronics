cmake_minimum_required (VERSION 2.6)

project (menu)

message ("Build menu library")

set (HEADER_FILES
    menu.h)

set (SOURCE_FILES
    menu.c)

add_executable (test_menu ${HEADER_FILES} ${SOURCE_FILES} main.c)
add_library (menu ${HEADER_FILES} ${SOURCE_FILES})

set (MENU_LIBRARY menu CACHE PATH "menu library available")
