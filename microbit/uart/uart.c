#include "uart.h"
#include "gpio.h"
#include <stdio.h>

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
	// Tasks 0x000
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED0[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESERVED1[56];
	// Events 0x100
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVED2[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED3;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED4[7];
	volatile uint32_t RXTO;
	volatile uint32_t RESERVED5[110];
	// Registers 0x300
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED6[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED7[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED8;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED9;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED10[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

// 24 - TXD - transmit - output
// 25 - RXD - receiver - input

// Need to set BAUD-rate 9600
// No flow controll
// 2 stop bits
// 8 bit packets

#define TXD_bp 24
#define RXD_bp 25
#define BAUDRATE_9600 0x00275000
#define ENABLE_UART 4

void uart_init()
{
	// Set TX to output and RX to input
	GPIO->DIR |= (1 << TXD_bp);
	GPIO->DIR &= ~(1 << RXD_bp);

	// Set UART to use these pins
	UART->PSELRXD = RXD_bp;
	UART->PSELTXD = TXD_bp;
	// We do not use CTS and RTS
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;

	// Set BAUDRATE
	UART->BAUDRATE = BAUDRATE_9600;

	// Enable UART
	UART->ENABLE = ENABLE_UART;

	// Receive messages
	UART->STARTRX = 1;
}

void uart_send(char data)
{
	// Start transmitting cycle
	UART->STARTTX = 1;
	UART->TXD = data;
	while (!(UART->TXDRDY));
}

char uart_read()
{
	char data = 0;
	printf("Enter char to be sent: ");
	data = getchar();

	if (!(UART->RXDRDY))
		data = '\0';
	else {
		UART->RXDRDY = 0;
		data = UART->RXD;
	}	

	return data;
}