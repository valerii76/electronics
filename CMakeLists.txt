cmake_minimum_required (VERSION 2.6)

include (winavr.cmake)

project (velocomp)

# The version number
set (velocomp_VERSION_MAJOR 0)
set (velocomp_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

include_directories (
    "${PROJECT_BINARY_DIR}"
    )

add_executable (velocomp
    src/main.c)
