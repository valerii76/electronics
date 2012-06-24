cmake_minimum_required (VERSION 2.6)

include (${BASE_DIRECTORY}/winavr.cmake)

project (velocomputer)

message ("Build velocomputer")

set (SOURCE_FILES
    src/main.c)

add_executable (velocomputer ${SOURCE_FILES})

AVR_CREATE_TEXT (velocomputer)
AVR_CREATE_LST (velocomputer)
AVR_CREATE_EEPROM (velocomputer)


add_dependencies (velocomputer ${LCD_LIBRARY})
target_link_libraries (velocomputer ${LCD_LIBRARY})
