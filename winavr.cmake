SET (CMAKE_SYSTEM_NAME Generic)
SET (CMAKE_C_COMPILER avr-gcc)
SET (CMAKE_CXX_COMPILER avr-g++)
SET (OBJ_COPY avr-objcopy)
SET (OBJ_DUMP avr-objdump)
SET (CSTANDARD "-std=gnu99")
SET (CDEBUG "-gstabs")
SET (CWARN "-Wall -Wstrict-prototypes")
SET (CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET (COPT "-Os")
SET (CMCU "-mmcu=atmega8")
SET (CDEFS "-DF_CPU=1000000L")

SET (CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CSTANDARD} ${CEXTRA}")
SET (CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")
SET (CMAKE_C_FLAGS ${CFLAGS})
SET (CMAKE_CXX_FLAGS ${CXXFLAGS})

macro (AVR_CREATE_TEXT name)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .text -j .data -O ihex ${name} ${name}.hex)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .text -j .data -O srec ${name} ${name}.srec)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .text -j .data -O binary ${name} ${name}.bin)
endmacro (AVR_CREATE_TEXT)

macro (AVR_CREATE_LST name)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_DUMP} ARGS -h -S ${name} > ${name}.lst)
endmacro (AVR_CREATE_LST)

macro (AVR_CREATE_EEPROM name)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .eeprom --change-section-lma .eeprom=0 -O ihex ${name} ${name}_eeprom.hex)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .eeprom --change-section-lma .eeprom=0 -O srec ${name} ${name}_eeprom.srec)
    add_custom_command (TARGET ${name} POST_BUILD COMMAND
        ${OBJ_COPY} ARGS -j .eeprom --change-section-lma .eeprom=0 -O binary ${name} ${name}_eeprom.bin)
endmacro (AVR_CREATE_EEPROM)
