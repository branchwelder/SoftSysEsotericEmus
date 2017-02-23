#include "emu.h"
#include <stdio.h>


// task1 pointer
struct task_cb *task1_ptr = NULL;

void task1() {
	// initialization
	// DDRB = 0xff;
	// PORTB = 0x00;
	//
	// while (1) {
	// 	PORTB ^= 0xff;
	// 	_delay_ms(100);
	// }
	printf("Hello\n");
}


void task2() {
	// initialization
	// DDRC = 0xff;
	// PORTC = 0x00;

	while (1) {
		// PORTC ^= 0xff;

		// explicitly put task1 to sleep
		// aos_sched_task_sleep(task1_ptr);

		// busy loop - will consume a lot of processing time
		//_delay_ms(200);

		printf("Goodbye\n");

		// awake task1
		// aos_sched_task_awake(task1_ptr);
	}
}


int main(void) {

	// initialize the system
	init();

	// create tasks
	task1_ptr = aos_task_create(task1, 32);
	aos_task_create(task2, 32);

	// start the scheduler
	run();
	return 0;
}
