#include "libfiber.h"
#include <stdio.h>

#include <avr/io.h>

#include <util/delay.h>

#include <unistd.h>

void blinkQuickly()
{
	#define BLINK_DELAY_Q 100

	/* set pin 5 of PORTB for output*/
  DDRB |= _BV(DDB5);

  while(1) {
		/* set pin 5 high to turn led on */
		PORTB |= _BV(PORTB5);
		_delay_ms(BLINK_DELAY_Q);
		/* set pin 5 low to turn led off */
		PORTB &= ~_BV(PORTB5);
		_delay_ms(BLINK_DELAY_Q);
	}
	fiberYield()
}

void blinkMedium()
{
	#define BLINK_DELAY_M 1000
	/* set pin 5 of PORTB for output*/
	DDRB |= _BV(DDB5);

	while(1) {
		/* set pin 5 high to turn led on */
		PORTB |= _BV(PORTB5);
		_delay_ms(BLINK_DELAY_M);
		/* set pin 5 low to turn led off */
		PORTB &= ~_BV(PORTB5);
		_delay_ms(BLINK_DELAY_M);
	}
	fiberYield()
}

void blinkSlowly()
{
	#define BLINK_DELAY_S 10000
		/* set pin 5 of PORTB for output*/
  DDRB |= _BV(DDB5);

	  while(1) {
		/* set pin 5 high to turn led on */
		PORTB |= _BV(PORTB5);
		_delay_ms(BLINK_DELAY_S);
		/* set pin 5 low to turn led off */
		PORTB &= ~_BV(PORTB5);
		_delay_ms(BLINK_DELAY_S);
	}
	fiberYield()
}

int main()
{
	/* Initialize the fiber library */
	initFibers();

	/* Go fibers! */
	spawnFiber( &blinkQuickly );
	spawnFiber( &blinkMedium );
	spawnFiber( &blinkSlowly );

	/* Since these are nonpre-emptive, we must allow them to run */
	waitForAllFibers();

	/* The program quits */
	return 0;
}
