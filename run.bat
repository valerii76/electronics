REM cd c:/avr
REM make clean
REM make
c:/avrdude/avrdude.exe -C c:/avrdude/avrdude.conf -c usbbit -B 38400 -p m8 -P ft0 -U flash:w:c:/work/electronics/build/src/velocomputer/velocomputer.hex:a
