cmake_minimum_required (VERSION 2.6)

project (all)

# Utility
add_subdirectory (utils)
include_directories (${BASE_DIRECTORY}/src/utils)

# Menu
add_subdirectory (libmenu)
include_directories (${BASE_DIRECTORY}/src/libmenu)

# TWI
add_subdirectory (libtwi)
include_directories (${BASE_DIRECTORY}/src/libtwi)

# LCD library
add_subdirectory (liblcd)
include_directories (${BASE_DIRECTORY}/src/liblcd)

# Main velocomputer project
add_subdirectory (velocomputer)
