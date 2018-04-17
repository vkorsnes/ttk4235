#include "twi.h" 

void twi_init() 
{
	// Configure GPIO
	GPIO->DIRSET |= (1 << SDA_PIN);
	GPIO->DIRSET |= (1 << SCL_PIN); 
	// S0D1 = Standard '0', Disconnect '1'
	GPIO->PIN_CNF[SDA_PIN] |= (S0D1 << DRIVE_CONF);
	GPIO->PIN_CNF[SCL_PIN] |= (S0D1 << DRIVE_CONF);
	GPIO->PIN_CNF[SDA_PIN] |= (3 << 2);
	GPIO->PIN_CNF[SCL_PIN] |= (3 << 2);


	// Configure TWI
	TWIO->PSELSCL = SCL_PIN;
	TWIO->PSELSDA = SDA_PIN;
	TWIO->FREQUENCY = KBPS100;
	TWIO->ENABLE = TWI_ENABLE;
}

void twi_multi_read (uint8_t slave_address,
					 uint8_t start_register,
					 int registers_to_read,
					 uint8_t *data_buffer)
{
	TWIO->ADDRESS = slave_address;
	
	TWIO->STARTTX = 1;
	TWIO->TXDSENT = 0;
	TWIO->TXD = start_register;
	while(!TWIO->TXDSENT);
	
	TWIO->RXREADY = 0;
	TWIO->STARTRX = 1;
	for (int i = 0; i < registers_to_read - 1; ++i) {
		while(!TWIO->RXREADY);
		*(data_buffer + i) = TWIO->RXD;
		TWIO->RXREADY = 0;
	}
	
	TWIO->STOP = 1;
	while(!TWIO->RXREADY);
	data_buffer[registers_to_read] = TWIO->RXD;
}

void twi_multi_write(uint8_t slave_address,
					 uint8_t start_register,
					 int registers_to_read,
					 uint8_t *data_buffer)
{
	TWIO->ADDRESS = slave_address;

	TWIO->STARTTX = 1;
	TWIO->TXDSENT = 0;
	TWIO->TXD = start_register;
	while(!TWIO->TXDSENT);
	for (int i = 0; i < registers_to_read; ++i) {
		TWIO->TXDSENT = 0;
		TWIO->TXD = *(data_buffer + i);
		while(!TWIO->TXDSENT);
	}

	TWIO->STOP = 1;
	
}