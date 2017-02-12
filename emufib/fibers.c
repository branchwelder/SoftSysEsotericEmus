/*
* emufib Threading Library
* fibers.c
* 
* Handle thread functions: init, create, yield, destroy
*/



/* INCLUDES */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>



/* THREAD DEFS */
#define MAX_THREADS 10
#define THREAD_STACK (1024*1024)

typedef struct
{
	void** stack;
	void* stack_bottom; /* malloc reference */
	int active;
} Thread;



/* THREAD PARAMS */
/* Queue of threads to init */
static fiber fiberList[ MAX_THREADS ];
/* Current thread */
static int currentThread = -1;
/* True if in fiber rather than main process */
static int inThread = 0;
/* Num active threads */
static int numThreads = 0;

/* Init a main thread */
static Thread mainThread;

/* Define context switching functions */
extern int asm_switch(thread* next, thread* current, int return_value);
static void initStack(thread* thread, int stack_size, void (*fptr)(void));
extern void* asm_call_thread_exit;



/* THREAD FUNCTIONS */
/* Create Stacks */
static void initStack(thread* thread, int stack_size, void (*fptr)(void)) {
	int i;
	#ifdef __x86_64
		/* x86-64: rbx, rbp, r12, r13, r14, r15 */
		static const int NUM_REGISTERS = 6;
	#else
		/* x86: ebx, ebp, edi, esi */
		static const int NUM_REGISTERS = 4;
	#endif
		assert(stack_size > 0);
		assert(fptr != NULL);

		/* Create a 16-byte aligned stack which will work on Mac OS X. */
		assert(stack_size % 16 == 0);
		thread->stack_bottom = malloc(stack_size);
		if (thread->stack_bottom == 0) return;
		thread->stack = (void**)((char*) thread->stack_bottom + stack_size);

	*(--thread->stack) = (void*) ((uintptr_t) &asm_call_thread_exit);
	*(--thread->stack) = (void*) ((uintptr_t) fptr);
	/* Init registers with NULL */
	for (i = 0; i < NUM_REGISTERS; ++i) {
		*(--thread->stack) = 0;
	}
}

// Init Threads
void initThreads()
{
	memset(threadList, 0, sizeof(threadList));
	mainThread.stack = NULL;
	mainThread.stack_bottom = NULL;
}

// Create Threads
int createThread( void (*func)(void) )
{
	if ( numFibers == MAX_FIBERS ) return 1; /* Max fibers error */

	/* Set the context to a new stack */
	create_stack( &threadList[numThreads], THREAD_STACK, func );
	if ( threadList[numThreads].stack_bottom == 0 )
	{
		printf( "Error: Could not allocate stack." );
		return 2; /* Malloc error */
	}
	threadList[numThreads].active = 1;
	++ numThreads;
	
	return 0; /* No error */
}

// Destroy Threads
void destroyThread() {
	assert( inThread );
	assert( 0 <= currentThread && currentThread < numThread );
	threadList[currentThread].active = 0;
	asm_switch( &mainThread, &threadList[currentThread], 0 );

	/* asm_switch should never return for an exiting fiber. */
	abort();
}