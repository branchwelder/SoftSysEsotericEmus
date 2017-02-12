#Sprint 2: Preliminary Report

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
- Set up C development toolchain for Arduino
- Alter the example.c file form libfiber to work on arduino
- Understand how to compile header files onto the Arduino
- Comment all unknown function in the libfiber-sjlj.c file
- Get Arduino blinking with pure C
- Implement a threading library with basic Pthread capabilities
      - Create
      - Run
      - Yeild
      - Join
- 

## Product Backlog
Check out our (updated) [Trello board](https://trello.com/b/3wvm9Qzs/softsysesotericemus "Esoteric Emus").

## Possible Roadblocks
- The number of sources on this topic will hopefully prevent and problems from halting project progress
- The learning curve associated with understanding the the functions that threading requires in C is quite high and will be challenging to overcome
- Arduinos and using C to code to Arduino can be finicky and might need need help with managing them
