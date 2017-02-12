#include "pca.h"
#include <avr/io.h>

#define TDELAY_IMPLEMENT_T0_INT 1

int main(void)
{
	DDRB = 0xff;
	PORTB = 0x00;

	tdelay_init(E_TIMER0);

	while (1) {
		PORTB ^= 0xff;
		tdelay_ms(E_TIMER0, 1000);
	}

	return 0;
}
