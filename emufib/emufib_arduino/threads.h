
/* INCLUDES */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pca.h"
#include <util/delay.h>

/* THREAD DEFS */
#define MAX_THREADS 10
#define THREAD_STACK (32*32)
#define ASM_PREFIX ""


typedef struct
{
	void** stack;
	void* stack_bottom; /* malloc reference */
	int active;
  uint8_t reg[32];
} thread;


/* Define context switching functions */
extern int asm_switch(thread* next, thread* current, int return_value);
extern void* asm_call_thread_exit;
static void createStack(thread* thread, int stack_size, void (*fptr)(void));


void initThreads();

int createThread( void (*func)(void) );


/* Context switching: REPLACE WITH ARDUINO VERSION */
void threadYield();

/* Let threads run after creation */
int waitForAllThreads();


// Destroy Threads
void destroyThread();
