cmake_minimum_required (VERSION 2.6)

project (devices)

message ("Build devices library")

set (HEADER_FILES
     ds18b20.h
     mpl115a.h)

set (SOURCE_FILES
     ds18b20.c
     mpl115a.c)

include_directories (${BASE_DIRECTORY}/src/utils)

add_library (devices ${HEADER_FILES} ${SOURCE_FILES})

add_dependencies (devices
                  ${UTILS_LIBRARY})

set (DEVICES_LIBRARY devices CACHE PATH "devices library available")
