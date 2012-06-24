REM cd c:/avr
REM make clean
REM make
c:/avr/avrdude.exe -C c:/avr/avrdude.conf -c usbbit -B 9600 -p m8 -P ft0 -U flash:w:c:/work/velocomp/build/src/velocomputer.hex:a
