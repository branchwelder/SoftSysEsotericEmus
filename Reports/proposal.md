# Sprint 1: Proposal

## Goals

### MVP
The minimal deliverable for this project will be an Arduino threading demo with visual outputs to show the capabilities of our threading library. We will first implement the basic functions of the C PThread library within our own library for Arduino. These functions will include creating, destroying, attaching, and detaching threads as well as initializing, destroying, locking, and unlocking mutexes.

### Stretch
Once the PThread demonstrations listed in the MVP are fully functional, we will add more functionality as time allows. Other development areas that we can explore are memory barriers, queues, and other advanced threading topics. Any of these features that we implement will be included on the final demonstration.

### Learning goals/errata
- Gain an understanding of using gcc and its many flags.
- Understand how Arduinos work and how they differ from computers that use operating systems.
- Understand what threading means and all of the basic functions involved.
- Understand what we are doing with the Arduino on a hardware level and how to address the microcontroller.
- Become more comfortable with pointers.

## Resources Required

### Annotated Bibliography
- <https://computing.llnl.gov/tutorials/pthreads/>: This is an overview of POSIX threads and the pthread library API. This could be useful for better understanding how pthreads work and understanding which functions we can add once we complete our MVP.
- <http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html>: POSIX thread libraries tutorial (covers thread basics, creation and termination, synchronization (with mutexes, joins, and condition variables), scheduling, and pitfalls).
- <http://homepage.divms.uiowa.edu/~jones/opsys/threads/>: A C threading package from 1998. May be outdated but will offer an idea of how to structure our code.
- <http://www.evanjones.ca/software/threading.html>: This is a fairly basic implementation of a user-level thread in C using two different functions for moving between threads. There is some overview of how threading works and also example code that is broken up into very basic and less basic. This will be helpful to model our first steps on.
- <https://github.com/ivanseidel/ArduinoThread>: A very complete Arduino threading library that includes advanced threading functions. This will help us work on threading in Arduino.
- <http://www.nongnu.org/avr-libc/>: C library for Ardunio gcc. This will be necessary for us to implement our program onto Arduino.

## Product Backlog
Check out our (updated) [Trello board](https://trello.com/b/3wvm9Qzs/softsysesotericemus "Esoteric Emus").

## Possible Roadblocks
- The number of sources on this topic will hopefully prevent and problems from halting project progress
- The learning curve associated with understanding the the functions that threading requires in C is quite high and will be challenging to overcome
- Arduinos and using C to code to Arduino can be finicky and might need need help with managing them
