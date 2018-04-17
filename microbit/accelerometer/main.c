#include <stdio.h>
#include <stdlib.h>

#include "twi.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include "utility.h"
#include "uart.h"

int main() 
{
	uart_init();
	twi_init();
	accel_init();
	ubit_led_matrix_init();
	
	int *data_buffer = (int *)malloc(3 * sizeof(int));
	int x_accel = 0;
	int y_accel = 0;
	int z_accel = 0;
	int x_dot = 0;
	int y_dot = 0;
	while (1) {
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 
			x_accel, y_accel, z_accel);
		accel_read_x_y_z(data_buffer);
		x_accel = data_buffer[0];
		y_accel = data_buffer[1];
		z_accel = data_buffer[2];

		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 
			x_accel, y_accel, z_accel);

		x_dot = x_accel/50;
		y_dot = -y_accel/50;

		ubit_led_matrix_light_only_at(x_dot, y_dot);
		int delay = 10000;
		while(--delay);
	}
}