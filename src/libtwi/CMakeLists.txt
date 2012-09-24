cmake_minimum_required (VERSION 2.6)

project (twi)

message ("Build twi library")

set (HEADER_FILES
    twi_master.h)

set (SOURCE_FILES
    twi_master.c)

add_library (twi ${HEADER_FILES} ${SOURCE_FILES})

set (TWI_LIBRARY twi CACHE PATH "twi library available")
