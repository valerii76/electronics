cmake_minimum_required (VERSION 2.6)

include (avr.cmake)

project (all)

set (BASE_DIRECTORY ${PROJECT_SOURCE_DIR})

add_subdirectory (${BASE_DIRECTORY}/src)
