#include <stdio.h>
#include "gpio.h"
#include "uart.h"

#define BUTTON_A_bp 17
#define BUTTON_B_bp 26

ssize_t _write(int fd, const void *buf, size_t count)
{
	char * letter = (char *)(buf);
	for (int i = 0; i < count; ++i) {
		uart_send(*letter);
		++letter;
	}
	return count;
}

int main()
{
	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_bp] = 0; // Button A
	GPIO->PIN_CNF[BUTTON_B_bp] = 0; // Button B

	uart_init();

	unsigned int delay = 0;

	for(int i = 4; i <= 15; i++) {
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	while(1){
		if (!(GPIO->IN & (1 << BUTTON_A_bp))) {
			uart_send('A');
		}
		if (!(GPIO->IN & (1 << BUTTON_B_bp))) {
			uart_send('B');
		}

		if (uart_read() == '\0');
		else {
			for (int i = 13; i < 16; i++){
				GPIO->OUT ^= (1 << i);
			}
			iprintf("Norway has %d countries.\n\r", 18);
		}

		delay = 100000;
		while(--delay);
	}
}