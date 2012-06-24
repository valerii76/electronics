cmake_minimum_required (VERSION 2.6)

include (winavr.cmake)

project (all)

set (BASE_DIRECTORY ${PROJECT_SOURCE_DIR})
include_directories (${BASE_DIRECTORY})

# The version number
set (velocomp_VERSION_MAJOR 0)
set (velocomp_VERSION_MINOR 1)

configure_file (
    "${BASE_DIRECTORY}/config.h.in"
    "${BASE_DIRECTORY}/config.h"
    )


set (LCD_PATH ${BASE_DIRECTORY}/src/liblcd)
include_directories (${LCD_PATH}/include)
add_subdirectory (${LCD_PATH})

add_subdirectory (${BASE_DIRECTORY}/src)
