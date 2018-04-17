#include "gpiote.h"

#define GPIOTE_EVENT 1
#define GPIOTE_TASK 3

#define PIN_SEL 8
#define BUTTON_A 17
#define LED_1 13
#define LED_2 14
#define LED_3 15

#define POLARITY_SEL 16
#define TOGGLE 3
#define HI_TO_LOW 2



void gpiote_init()
{
	// Button A
	GPIOTE->CONFIG[0] = (GPIOTE_EVENT) | (BUTTON_A << PIN_SEL) | (HI_TO_LOW << POLARITY_SEL);

	// LEDs
	GPIOTE->CONFIG[1] = (GPIOTE_TASK) | (LED_1 << PIN_SEL) | (TOGGLE << POLARITY_SEL);
	GPIOTE->CONFIG[2] = (GPIOTE_TASK) | (LED_2 << PIN_SEL) | (TOGGLE << POLARITY_SEL);
	GPIOTE->CONFIG[3] = (GPIOTE_TASK) | (LED_3 << PIN_SEL) | (TOGGLE << POLARITY_SEL);
}