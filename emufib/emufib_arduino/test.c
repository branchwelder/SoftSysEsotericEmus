#include <stdio.h>
#include <stdlib.h>
#include "threads.c"

#include "pca.h"
#include <util/delay.h>


void task1() {
	while (1) {
		printf("Task 1\n");
		_delay_ms(200);
	}
	threadYield();
}


void task2() {
	while (1) {
		printf("Task 2222\n");
		_delay_ms(200);
	}
	threadYield();
}


int main(void) {
	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();
	serial_install_stdio();

	// initialize the system
	initThreads();

	// create tasks
	createThread(&task1);
	createThread(&task2);

	waitForAllThreads();

	return 0;
}
