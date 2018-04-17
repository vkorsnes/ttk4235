#include <stdio.h>
#include <stdlib.h>

#include "pwm.h"
#include "accel.h"
#include "uart.h"
#include "utility.h"
#include "twi.h"

int main ()
{
	int prescaler = 6;
	int period = 5064;
	int init_duty = period*0.075;

	pwm_init(prescaler, period, init_duty);
	twi_init();
	accel_init();
	uart_init();

	
	int *data_buffer = (int *)malloc(3 * sizeof(int));
	int x_accel = 0;
	int x_dot = 0;


	while(1) {
		accel_read_x_y_z(data_buffer);
		x_accel = data_buffer[0];

		x_dot = x_accel/2;
		utility_print(&uart_send, "X: %6d \n\r", x_dot);

		pwm_set_ticks(init_duty + x_dot);
	}
}