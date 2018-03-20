#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main()
{
	for(int i = 4; i <= 15; i++) {
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	gpiote_init();
	ppi_init();

	unsigned int delay = 0;
	while(1) {


		delay = 100000;
		while(--delay);
	}
}