#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include <avr/io.h>

/*
uint8_t mcp2515_init()
{
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset-command
	
	// Self-test
	mcp2515_read(MCP_CANSTAT, &value);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf(”MCP2515 is NOT in configuration mode after reset!\n”);
		return 1;
	}

	// More initialization

	return 0;
}


*/
uint8_t MCP2515_read(uint8_t address)
{
	uint8_t result;

	//select CAN-controller
	CLEAR_BIT(PORTB,PB4);

	//send read instrucion
	SPI_write(MCP_READ);

	//send address
	SPI_write(address);

	//read result
	result = SPI_read();

	return result;
}

void mcp2515_write(uint8_t data)
{

}
