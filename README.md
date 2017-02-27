# EsotericEmus

## Description

Emufib is a threading library developed to run on an Arduino architecture.  The library provides standard threading capabilities including 

* init() 
* create()
* yield()
* destroy()

The test files include an Arduino threading demo to show the capabilities of emufib including all of the basic PThread functions.  

All of the instructions for both running the example code and integrating emufib within your own project can be found below. 

**Project Website**

For more background, videos, and examples, check out the project site [here](https://hannahtwiggsmith.github.io/SoftSysEsotericEmus/).

## Authors

Hannah Twigg-Smith, Emma Price, Kathryn Hite

## Getting Started

### Required libraries

[AVR LibC](http://www.nongnu.org/avr-libc/) is required to compile C code on to the Arduino.  To install, run

`$ sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude`

Alternatively, you can navigate to the `libraries/avr-libc-1.8.1` directory and run

```
$ ./configure --prefix=$PREFIX --build=`./config.guess` --host=avr
$ make
$ make install
```

### Running the Serial Test

To test the serial connection to the Arduino in C, navigate to the `emufib/serial_test` directory and run

`$ make && make install`

Note that you may need to change the Arduino port definition in the Makefile to match the one on your machine. The port definition will be different for different machines and may include `ACM`, `COM`, or `usbmotem`. 

## Usage

### Arduino Test

The `emufib/threading_arduino` directory contains the source code for the threading library as well as a test file running multiple parallel tasks.  Follow the instructions below to upload the test to your Arduino.  Again, ensure that the Arduino port listed in the Makefile matches the one on your machine.  Mine was `/dev/cu.usbmodem1411`, so you will replace this in the final two commands below as well.  


```
$ make
$ avrdude -F -V -c arduino -p ATMEGA328P -P /dev/cu.usbmodem1411 -b 115200 -U flash:w:test.hex
$ screen /dev/cu.usbmodem1411
```

### Using emufib in Your Arduino C Application

To create a new C application utilizing the library, copy the `emu.c` and `emu.h` files from `emufib/threading_arduino` into your project directory.  Be sure to include `emu.h` in the C file where you are using Arduino threading.  Then compile your project with the following commands, replacing `test` with your filename and `/dev/ttyACM0` with your Arduino port:

```
$ avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o test.o test.c
$ avr-gcc -mmcu=atmega328p test.o -o test
$ avr-objcopy -O ihex -R .eeprom test test.hex
$ avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:test.hex
```

These tests were run using an Arduino Uno r3.  If you are using a different Arduino, you may need to change ATMEGA328P in the second and fourth commands to match the chip on your model.

### Standalone Usage

The emufib library can also be used on normal machine architecture by using the `threads.c` and `utils.h` from the `emufib/threading_purec` directory.  Copy the files to your project directory (again including `emu.c` in your C file).  This will give you the standard PThread functionality.  You can also run `./thread_test` in the `purec` directory to run the executable and test the threading capabilities.

## License

MIT License

Copyright (c) 2017 Hannah Twigg-Smith, Emma Price, Kathryn Hite

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

