/*
* emufib Threading Library
* thread_test.c
* 
* Test the functionality of the emufib threading library
*/

/* Threading library */
#include "threads.c"

int up = 0;
int down = 0;

// Task 1
void countUp() {
	while (up < 10) {
		up++;
	}
	threadYield();
}

// Task 2
void countDown() {
	while (down > -10) {
		down--;
	}
	threadYield();
}

int main(void) {
	printf("%i\n", up);
	printf("%i\n", down);

	// Initialize the thread list
	initThreads();

	// Create threads using our tasks
	createThread( &countUp );
	createThread( &countDown );

	// Run the threads with context switching
	waitForAllThreads();

	printf("%i\n", up);
	printf("%i\n", down);

	return 0;
}