/*
* emufib Threading Library
* threads.c
*
* Handle thread functions: init, create, yield, destroy
*/

/* INCLUDES */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pca.h"
#include <util/delay.h>
#include "threads.h"

/* THREAD PARAMS */
/* Queue of threads to init */

static thread threadList[MAX_THREADS];
/* Current thread */
static int currentThread = -1;
/* True if in thread rather than main process */
static int inThread = 0;
/* Num active threads */
static int numThreads = 0;

/* Init a main thread */
static thread mainThread;

/* THREAD FUNCTIONS */

/* 
* initThreads 
* 
* Initializes the thread list and the main thread.  Call this before creating any
* threads.
*/
void initThreads()
{
	DDRC = 0x01;
	PORTC = 0x00;
	int i = 0;

	while (i<2) {
		PORTC ^= 0x01;
		_delay_ms(200);
		i++;
	}
	memset(threadList, 0, sizeof(threadList));
	mainThread.stack = NULL;
	mainThread.stack_bottom = NULL;
}

/*
* createThread
*
* Pass in a pointer to a task function to create a new thread.  Switches contexts and 
* creates the appropriate stack in memory, adding to the thread list.
*/

int createThread( void (*func)(void) )
{

		DDRB = 0x01;
		PORTB = 0x00;
		int i = 0;

		while (i<2) {
			PORTB ^= 0x01;
			_delay_ms(200);
			i++;
		}
		
	if ( numThreads == MAX_THREADS ) return 1; /* Max threads error */
	/* Set the context to a new stack */
	createStack( &threadList[numThreads], THREAD_STACK, func );
	if ( threadList[numThreads].stack_bottom == 0 ){
		return 2; /* Malloc error */

	}
	threadList[numThreads].active = 1;
	++ numThreads;


	return 0; /* No error */
}

/* 
* threadYield
* 
* Provides context switching between threads.
* If currently in a thread, it will switch to the main context.  Otherwise, it will
* save the current state and switch in a new thread to the main context.
*/
void threadYield()
{
	/* If we are in a thread, switch to the main process */
	if ( inThread )
	{
		/* Switch to the main context */

		asm_switch( &mainThread, &threadList[currentThread], 0 );
	}
	/* Else, we are in the main process and we need to dispatch a new fiber */
	else
	{
		if ( numThreads == 0 ) return;

		/* Saved the state so call the next fiber */
		currentThread = (currentThread + 1) % numThreads;
		inThread = 1;
		asm_switch( &threadList[ currentThread ], &mainThread, 0 );
		inThread = 0;

		if ( threadList[currentThread].active == 0 )
		{
			/* Free the "current" fiber's stack pointer */
			free( threadList[currentThread].stack_bottom );

			/* Swap the last fiber with the current, now empty, entry */
			-- numThreads;
			if ( currentThread != numThreads )
			{
				threadList[ currentThread ] = threadList[ numThreads ];
			}
			threadList[ numThreads ].active = 0;
		}

	}
	return;
}

/* 
* waitForAllThreads 
*
* Run and yield all threads until the processess finish. 
*/
int waitForAllThreads()
{
	int threadsRemaining = 0;

	/* If we are in a fiber, wait for all the *other* fibers to quit */
	if ( inThread ) threadsRemaining = 1;

	/* Execute the fibers until they quit */
	while ( numThreads > threadsRemaining )
	{
		threadYield();
	}

	return 0;
}

/*
* destroyThread
*
* Switch to the main context and destroy threads when the thread list reaches 0.
*/
void destroyThread() {
	assert( inThread );
	assert( 0 <= currentThread && currentThread < numThreads );
	threadList[currentThread].active = 0;
	asm_switch( &mainThread, &threadList[currentThread], 0 );

	/* asm_switch should never return for an exiting thread. */
	abort();
}

/* DEFINE ARCHITECTURE PARAMS */
/* REPLACE WITH ARDUINO VERSION */

__asm__ (".globl " ASM_PREFIX "asm_call_thread_exit\n"
ASM_PREFIX "asm_call_thread_exit:\n"
/*"\t.type asm_call_thread_exit, @function\n"*/
"\tcall " ASM_PREFIX "destroyThread\n");

/* 
* createStack 
* 
* Allocates a new stack in memory.  
* Takes in a pointer to the appropriate thread id, the size of the stack to be 
* allocated, and a pointer to the task function for the thread.
*/
static void createStack(thread* thread, int stack_size, void (*fptr)(void)) {

	int i;

	static const int NUM_REGISTERS = 32;

	assert(stack_size > 0);
	assert(fptr != NULL);

	thread->stack_bottom = malloc(stack_size);
	if (thread->stack_bottom == 0){
		return;
	}
	thread->stack = (void**)((char*) thread->stack_bottom + stack_size);

	*(--thread->stack) = (void*) ((uintptr_t) &asm_call_thread_exit);
	*(--thread->stack) = (void*) ((uintptr_t) fptr);
	/* Init registers with NULL */
	for (i = 0; i < NUM_REGISTERS; ++i) {
		*(--thread->stack) = 0;
		DDRC = 0x01;
		PORTC = 0x00;
		int j = 0;

		while (j<2) {
			PORTC ^= 0x01;
			_delay_ms(200);
			j++;
			}
		}
	}


__asm__ (".globl " ASM_PREFIX "asm_switch\n"
ASM_PREFIX "asm_switch:\n"
"\t.type asm_switch, @function\n");

/* Move return value into rax */
__asm__ ("movw  r24, r4");
__asm__ ("movw  r30, r2");

/* save registers: rbx rbp r12 r13 r14 r15 (rsp into structure) */
__asm__ ("\tpush r31\n"
"\tin r31, 0x3f\n"
"\tpush r31\n"
"\tpush r30\n"
"\tpush r29\n"
"\tpush r28\n"
"\tpush r27\n"
"\tpush r26\n"
"\tpush r25\n"
"\tpush r24\n"
"\tpush r23\n"
"\tpush r22\n"
"\tpush r21\n"
"\tpush r20\n"
"\tpush r19\n"
"\tpush r18\n"
"\tpush r17\n"
"\tpush r16\n"
"\tpush r15\n"
"\tpush r14\n"
"\tpush r13\n"
"\tpush r12\n"
"\tpush r11\n"
"\tpush r10\n"
"\tpush r9\n"
"\tpush r8\n"
"\tpush r7\n"
"\tpush r6\n"
"\tpush r5\n"
"\tpush r4\n"
"\tpush r3\n"
"\tpush r2\n"
"\tpush r1\n"
"\tclr r1\n"
"\tpush r0\n");

/* restore registers */
__asm__ ("\tpop r0\n"
"\tpop r1\n"
"\tpop r2\n"
"\tpop r3\n"
"\tpop r4\n"
"\tpop r5\n"
"\tpop r6\n"
"\tpop r7\n"
"\tpop r8\n"
"\tpop r9\n"
"\tpop r10\n"
"\tpop r11\n"
"\tpop r12\n"
"\tpop r13\n"
"\tpop r14\n"
"\tpop r15\n"
"\tpop r16\n"
"\tpop r17\n"
"\tpop r18\n"
"\tpop r19\n"
"\tpop r20\n"
"\tpop r21\n"
"\tpop r22\n"
"\tpop r23\n"
"\tpop r24\n"
"\tpop r25\n"
"\tpop r26\n"
"\tpop r27\n"
"\tpop r28\n"
"\tpop r29\n"
"\tpop r30\n"
"\tpop r31\n"
"\tout 0x3f, r31\n"
"\tpop r31\n"

/* return to the "next" thread */
"\tret\n");
