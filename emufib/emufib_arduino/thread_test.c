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

void countUp() {
	while (up < 10) {
		up++;
	}
	threadYield();
}

void countDown() {
	while (down > -10) {
		down--;
	}
	threadYield();
}

int main(void) {
	printf("%i\n", up);
	printf("%i\n", down);

	initThreads();

	createThread( &countUp );
	createThread( &countDown );

	waitForAllThreads();

	printf("%i\n", up);
	printf("%i\n", down);

	return 0;
}
