/*
* emufib Threading Library
* fibers.c
* 
* Handle thread functions: init, create, yield, destroy
*/

/* Includes */

/* Struct definition of a stack */
typedef struct
{
	void** stack;
	void* stack_bottom; /* malloc reference */
	int active;
} Thread;

/* Def threading params */
/* Current thread */
static int currentFiber = -1;
/* True if in fiber rather than main process */
static int inFiber = 0;
/* Num active threads */
static int numFibers = 0;

static Thread mainThread;

// Allocate a Stack
void initStack() {

}

// Init Threads
void initThread() {

}

// Create Threads
void createThread() {

}

// Yielding
void yeild() {

}

// Destroy Threads
void destryThread() {

}

// Main