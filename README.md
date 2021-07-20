# SuitTrackerMicro

### Project members
- Piccinini Luca
- Sarin Gaston
- Fontana Alexis

### Project description
In this repository will stay the code for the micro Atmega328p and ESP8266, what will used for the data compiler and your transmission.

## Atmega328p
For work with atmega328p in Arduino Uno, we will used the next tools:
- binutils : for getting tools like assembler, linker
- gcc-avr : a GNU C cross-compiler for specifically for AVR
- avr-libc: it is a package for AVR C library
- avrdude: it is a utility that transfers codes from the UBUNTU to the microcontroller. Here we will be using the CLI tool of avrdude.

All process will realized in Ubuntu 20.04 and will used make for agilized the process the compiler and upload of code.


## ESP8266
### MicroPython
Micropython is a minimal version of Python, which is intended for microcontrollers. We chose this firmware to become independent from the arduino IDE. Finally, it is applicable the advantages of python and its community.
### Firmware change
The whole process was done in ubuntu 20.04. Basically it can be summarized as follows:
- Install python and pip, recomend visit [python](www.python.org )
- Install esptool, if use pip, the comand is pip install esptool
- Dowload firmware, [micropython](www.micropython.org)