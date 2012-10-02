cmake_minimum_required (VERSION 2.6)

project (devices)

message ("Build devices library")

set (HEADER_FILES
     mpl115a.h)

set (SOURCE_FILES
     mpl115a.c)

add_library (devices ${HEADER_FILES} ${SOURCE_FILES})

set (DEVICES_LIBRARY devices CACHE PATH "devices library available")
