#include <stdio.h>
#include <stdlib.h>
#include "emu.h"

#include "pca.h"
#include <util/delay.h>


// task1 pointer
struct task_cb *task1_ptr = NULL;

void task1(void *a_data UNUSED) {
	while (1) {
		printf("Task 1\n");
		_delay_ms(200);
	}
}


void task2(void *a_data UNUSED) {
	while (1) {
		printf("Task 2222\n");
		_delay_ms(200);
	}
}


int main(void) {
	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();
	serial_install_stdio();

	printf("*******************************\n");

	printf("Init is about to run.\n");

	// initialize the system
	init();
	printf("System initialized.\n");

	// create tasks
	aos_task_create(task1, NULL, 32);
	aos_task_create(task2, NULL, 32);

	printf("Created tasks.\n");

	// start the scheduler
	printf("About to run tasks.\n");

	run();

	printf("Passed run.\n");

	while (1) {
		printf("dead to us.\n");
	}
	return 0;
}
