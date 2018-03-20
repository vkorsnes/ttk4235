#include "uart.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
	// Tasks 0x000
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESERVED[56];
	// Events 0x100
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVED[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED[7];
	volatile uint32_t RXTO;
	volatile uint32_t RESERVED[110];
	// Registers 0x300
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED[21];
	volatile uint32_t CTS;
} NRF_UART_REG;