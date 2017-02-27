Emufib is a threading library developed to run on an Arduino architecture.  The library provides standard threading capabilities including 

* init() 
* create()
* yield()
* destroy()

The test files include an Arduino threading demo to show the capabilities of emufib including all of the basic PThread functions.  All of the instructions for both running the example code and integrating emufib within your own project can be found below.

**Background**

Provide context for your project by describing the broader space in which it is situated. This section will likely draw upon your annotated bibliography. You've already collected this knowledge and shown us you understand it, now frame it for an external audience.

**Implementation**

What specifically did you accomplish with this project? Within the context of the problem space, enumerate the potential options and explain why you chose what you did. Describe what makes it interesting/challenging, and how you overcame those challenges. Explain your implementation and design decisions with sufficient detail for a technical audience to understand it.

**Results**

The pure C version of the library works as expected, switching between threads correctly as indicated in the example.  The pure C library can be used to show that the background threading functionality is correctly implemented before porting to the Arduino architecture.  Basic PThread functionality is included, so the files can also be used as a lightwight threading option for C projects.

![Pure C Demo](./images/thread_test.png)

To debug the Arduino, it is possible to open up a serial connection using the provided C library as described in the README.  However, this can negatively alter the threading registers and create memory problems, so it is not recommended as a debugging method within threads.

![Serial Demo](./images/serial.jpg)

The Arduino test setup allows debugging via LED lights to prevent serial print statements from altering thread registers in the program.  Writing to an LED is fast and simple in assembly, and example write commands can be found in the test files.

![Arduino Demo](./images/emufib.png)

The final Arduino test video below shows two LEDs successfully running on parallel threads to blink at different rates.  This 

FINAL VIDEO HERE

**Project Authors**

Hannah Twigg-Smith, Emma Price, Kathryn Hite

**Project License**

This project is licensed using the MIT License.  See the [README](https://github.com/hannahtwiggsmith/SoftSysEsotericEmus/blob/master/README.md) for more details.
