#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	// 700 - 520 = e
	// 1E0_16 = 480_10
	// 480/4 = 4
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

#define BUTTON_A_bp 17
#define BUTTON_B_bp 26

int main()
{
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++) {
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_bp] = 0; // Button A
	GPIO->PIN_CNF[BUTTON_B_bp] = 0; // Button B


	int sleep = 0;
	while(1) {

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << BUTTON_A_bp))) {
			for (int i = 13; i < 16; ++i) {
				GPIO->OUTSET = (1 << i);
			}
		}
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << BUTTON_B_bp))) {
			for (int i = 13; i < 16; ++i) {
				GPIO->OUTCLR = (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
