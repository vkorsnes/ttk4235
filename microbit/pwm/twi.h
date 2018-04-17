#ifndef _TWI_H
#define _TWI_H

#include <stdint.h>
#include "gpio.h"

#define TWIO ((NRF_TWI_REG*)0x40003000)
typedef struct {
	// TASKS
	volatile uint32_t STARTRX;
	volatile uint32_t TWI_RESERVED_0;
	volatile uint32_t STARTTX;
	volatile uint32_t TWI_RESERVED_1[2];
	volatile uint32_t STOP;
	volatile uint32_t TWI_RESERVED_2;
	volatile uint32_t SUSPEND;
	volatile uint32_t RESUME;
	volatile uint32_t TWI_RESERVED_3[56];
	// EVENTS
	volatile uint32_t STOPPED;
	volatile uint32_t RXREADY;
	volatile uint32_t TWI_RESERVED_4[4];
	volatile uint32_t TXDSENT;
	volatile uint32_t TWI_RESERVED_5;
	volatile uint32_t ERROR;
	volatile uint32_t TWI_RESERVED_6[4];
	volatile uint32_t BB;
	volatile uint32_t TWI_RESERVED_7[49];
	// REGISTERS
	volatile uint32_t SHORTS;
	volatile uint32_t TWI_RESERVED_8[63];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t TWI_RESERVED_9[110];
	volatile uint32_t ERRORSRC;
	volatile uint32_t TWI_RESERVED_10[14];
	volatile uint32_t ENABLE;
	volatile uint32_t TWI_RESERVED_11;
	volatile uint32_t PSELSCL;
	volatile uint32_t PSELSDA;
	volatile uint32_t TWI_RESERVED_12[2];
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t TWI_RESERVED_13;
	volatile uint32_t FREQUENCY;
	volatile uint32_t TWI_RESERVED_14[24];
	volatile uint32_t ADDRESS;
} NRF_TWI_REG;

#define SDA_PIN 30
#define SCL_PIN 0
#define DRIVE_CONF 8
#define S0D1 6

#define TWI_ENABLE 5
#define KBPS100 0x01980000

void twi_init();

void twi_multi_read(uint8_t slave_address,
					uint8_t start_register,
					int registers_to_read,
					uint8_t *data_buffer);

void twi_multi_write(uint8_t slave_address,
					 uint8_t start_register,
					 int registers_to_read,
					 uint8_t *data_buffer);
#endif // !_TWI_H