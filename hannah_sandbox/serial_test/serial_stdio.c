#include "pca.h"
#include <util/delay.h>

int main(void)
{
	int cnt = 0;

	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();
	serial_install_stdio();

	while(1) {
		printf("EsotericEmus tessdft. Line: [%d]\n", cnt++);
		_delay_ms(1000);
	}

	return 0;
}
