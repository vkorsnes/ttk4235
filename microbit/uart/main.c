#include "gpio.h"
#include "uart.h"

#define BUTTON_A_bp 17
#define BUTTON_B_bp 26

int main()
{
	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_bp] = 0; // Button A
	GPIO->PIN_CNF[BUTTON_B_bp] = 0; // Button B

	uart_init();

	unsigned int delay = 0;

	while(1){
		if (!(GPIO->IN & (1 << BUTTON_A_bp))) {
			uart_send('A');
		}
		if (!(GPIO->IN & (1 << BUTTON_B_bp))) {
			uart_send('B');
		}

		delay = 100000;
		while(--delay);
	}
}