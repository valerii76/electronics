cmake_minimum_required (VERSION 2.6)

project (velocomputer)

message ("Build velocomputer")

# The version number
set (velocomp_VERSION_MAJOR 0)
set (velocomp_VERSION_MINOR 1)

configure_file (
    ${BASE_DIRECTORY}/src/velocomputer/config.h.in
    ${BASE_DIRECTORY}/src/velocomputer/config.h
    )

set (LCD_PATH ${BASE_DIRECTORY}/src/liblcd)
include_directories (${BASE_DIRECTORY}/src/velocomputer)

set (SOURCE_FILES
    main.c)

add_executable (velocomputer ${SOURCE_FILES})

AVR_CREATE_TEXT (velocomputer)
AVR_CREATE_LST (velocomputer)
AVR_CREATE_EEPROM (velocomputer)

add_dependencies (velocomputer ${LCD_LIBRARY} ${UTILS_LIBRARY})
target_link_libraries (velocomputer ${LCD_LIBRARY} ${UTILS_LIBRARY})
