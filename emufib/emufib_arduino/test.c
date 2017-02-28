#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

#include <avr/io.h>
#include "pca.h"
#include <util/delay.h>


void task1() {
	DDRC = 0x01;
	PORTC = 0x00;
	int i = 0;

	while (i<2) {
		PORTC ^= 0x01;
		_delay_ms(1000);
		i++;
	}
	printf("about to yield 1 \n");
	threadYield();
}


void task2() {
	printf("about to yield 2 \n");
	DDRB = 0x01;
	PORTB = 0x00;
	int i = 0;
	while (i<2) {
		PORTB ^= 0x01;
		_delay_ms(1000);
		i++;
	}
	printf("about to yield 2 \n");
	threadYield();
}


int main(void) {
	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();
	serial_install_stdio();

	// initialize the system
	printf("init\n");
	initThreads();

	// create tasks
	printf("create\n");
	createThread( &task1 );
	createThread( &task2 );

	waitForAllThreads();

	printf("done\n");

	return 0;
}
