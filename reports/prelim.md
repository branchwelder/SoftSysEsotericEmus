# Sprint 2: Preliminary Report

## Goals

**MVP**

The minimal deliverable for this project will be an Arduino threading demo with visual outputs to show the capabilities of our threading library. We will first implement the basic functions of the C PThread library within our own library for Arduino. These functions will include creating, running, destroying, yielding, and joining threads as well as initializing, destroying, locking, and unlocking mutexes.

**Stretch**

Once the threading capabilities listed in the MVP are fully implemented, we will add more functionality as time allows. Other development areas that we can explore are memory barriers, queues, and other advanced threading topics. Any of these features that we implement will be included on the final demonstration.

**Learning Goals**

* Gain an understanding of using gcc and its many flags.
* Understand how Arduinos work and how they differ from computers that use operating systems.
* Understand what threading means and all of the basic functions involved.
* Understand what we are doing with the Arduino on a hardware level and how to address the microcontroller.
* Understand stack and memory allocation

## Annotated Trello Cards

Check out our (updated) [Trello board](https://trello.com/b/3wvm9Qzs/softsysesotericemus). We added descriptions for all project-related cards that include links to evidence that the work has been done. We also added labels to better sort our cards, and made sure that all past cards are up to the current standards. We now have separate lists for project-related work and class-related work such as readings and exercises. We take ourselves off of the cards for class-related work once we have completed them, so we know who still has to do that task.

## Preliminary Results

**Understanding Threading**

In order to implement threading on an Arduino, we first wanted to understand how threading worked on a conceptual level. For this, we read the Head First C chapter on threading which explained how threads work, possible downfalls, and why they are useful. We also read through Think OS chapter 9 on PThreading which focused on implementation using a counter and the PThread library.

From there, we examined other implementations of user-level threading in C. After we found several other implementations, we all attempted to use them on our systems. Some of these programs were outdated and we could not use them, but others were successful and we modeled our implementation on them.

One of those successful implementations was the [libfiber library](http://www.evanjones.ca/software/threading.html). Which is fairly simple and includes all of the functions that we want to include in our most basic implementations. We modeled the majority of our implementation on this library, as explained below.

**Working with the Arduino**

The first Arduino implementation that we created is a blinking LED program that proves the functionality of our avr-libc toolchain used to compile C onto the Arduino.  This toolchain now handles the libraries and header files that we need to implement basic threading capabilities.

The libfiber threading library discussed above also currently runs on the Arduino with the basic init, create, yield, and destroy capabilities.  After finishing the development of our own threading library, we will focus on porting it to the Arduino as well during Sprint 3. To display this functionality, the Arduino is also hooked up to a test platform consisting of LEDs that can be used to display multiple running threads.  We are also able to send debugging messages via serial in C from the Arduino, which will allow us to confirm parameters like memory allocation and stack location. An example of this code can be found [here](https://github.com/hannahtwiggsmith/SoftSysEsotericEmus/tree/master/hannah_sandbox/serial_test).

**Writing the emufib Library**

Building on our understanding of threading and compilation capabilities on the Arduino, we have constructed a threading library called emufib.  The purpose of emufib is to act as a lightweight threading library that can run on the Arduino, properly allocating memory and controlling thread functions.  The functions currently include:

* Initializing threads
* Creating individual threads
* Yielding between threads
* Destroying threads

![emufib Library Results](/images/emufib.png "Working example of the emufib library.")

Because testing on our individual machines was successful, we will focus this coming sprint on porting our library over to the Arduino as well as adding further thread and mutex capabilities.  In order to make this happen, we are working on manipulating the Arduino memory to properly allocate multiple stacks for threads.  We are also adding functionality such as yielding to our thread definitions, and writing a mutex definition that includes creating, locking, and unlocking mutexes.

Due to overcoming the Arduino communication and compilation roadblocks from this past sprint, we should be able to demonstrate both our MVP and at least one stretch goal at the end of sprint 3.

## Resources for Future Work

Annotated Bibliography

https://github.com/dagon666/avr_Libpca
This library allows us to include functionality that would be given to us by the Arduino IDE in pure C.

https://pcarduino.blogspot.com/
This blog was written by the same person who created the avr-Libpca library. Each post describes some small project on implementing something in pure C for Arduino, such as connecting to the serial monitor, blinking an LED, creating a CLI, adding delays, etc.

https://computing.llnl.gov/tutorials/pthreads/
This is an overview of POSIX threads and the pthread library API. This could be useful for better understanding how pthreads work and understanding which functions we can add once we complete our MVP.

http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
POSIX thread libraries tutorial (covers thread basics, creation and termination, synchronization (with mutexes, joins, and condition variables), scheduling, and pitfalls).

http://www.evanjones.ca/software/threading.html
This is a fairly basic implementation of a user-level thread in C using two different functions for moving between threads. There is some overview of how threading works and also example code, that is broken up into very basic and less basic. This is what our main threading program is modeled on and will be helpful to reference for future work.

https://github.com/ivanseidel/ArduinoThread
A very complete Arduino threading library that includes advanced threading functions. This will help us work on threading in Arduino.

http://www.nongnu.org/avr-libc/
C library for Arduino gcc. This will be necessary for us to implement our program on Arduino.

https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html#Signal-Handling
This is the library on the signal function. Our current implementation of threading does not use signals, but many do and this will be helpful if we go in the direction of using signals.

https://cdn-learn.adafruit.com/downloads/pdf/memories-of-an-arduino.pdf
An overview of Arduino’s memory system, including how to find more of it. This will be very helpful when we begin to deal with Arduino memory and stack allocation.

## Sprint 3 Backlog

Again, check out our (updated) [Trello board](https://trello.com/b/3wvm9Qzs/softsysesotericemus). We did preliminary Sprint 3 planning and added the cards we think we need.

## Possible Roadblocks

**Sprint 2 Past Roadblocks:**

The potential roadblocks that we identified at the beginning of the past sprint were resolved as we moved through the initial development process.  The problems of communicating with the Arduino via serial in C as well as compiling C code and the associated header files have been solved.  We can now send serial debugging output to confirm that threading implementations are working on the Arduino.  We can also compile C libraries and our own header files to export to the Arduino.

**Sprint 3 Potential Roadblocks:**

Allocating stack memory within the SRAM on Arduino; we haven’t had much of a chance to look into this yet and it could pose a problem.
We may run into problems with context switching on the Arduino due to the different architecture, but have not had issues yet while running on Linux
