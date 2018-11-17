#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include <avr/io.h>


uint8_t MCP_init()
{

	MCP_reset();

	//aksel og de setter can i loopback mode, så i normal mode her inne. 
	//uint8_t value;
	//SPI_init(); // Initialize SPI
	//MCP2515_reset(); // Send reset-command
	
	// Self-test
	/*MCP2515_read(MCP_CANSTAT, &value);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf(”MCP2515 is NOT in configuration mode after reset!\n”);
		return 1;
	}
	*/
	// More initialization

	return 0;
	
}



uint8_t MCP_read(uint8_t address)
{
	CLEAR_BIT(PORTB, PB7); 

	uint8_t result;

	//select CAN-controller
	

	//send read instrucion
	SPI_write(MCP_READ);

	//send address
	SPI_write(address);

	//read result
	result = SPI_read();

	SET_BIT(PORTB, PB7); 


	return result;
}

void MCP_read_n_byte(int8_t *data,uint8_t address, uint8_t num_bytes)
{

	CLEAR_BIT(PORTB, PB7); 
	//select CAN-controller
	

	//send read instrucion
	SPI_write(MCP_READ);

	//send address
	SPI_write(address);

	for(int i =0; i<num_bytes;i++)
	{
		data[i] = SPI_read();
	}	

	SET_BIT(PORTB, PB7); 
}



void MCP_write(int8_t data, uint8_t address)
{
	//select CAN-controller
	CLEAR_BIT(PORTB, PB7); 

	//send write instruction
	SPI_write(MCP_WRITE);

	//send address
	SPI_write(address);

	//send data
	SPI_write(data);

	SET_BIT(PORTB, PB7); 


}

void MCP_write_n_byte(int8_t *data, uint8_t address, uint8_t num_bytes)
{
	//select CAN-controller
	CLEAR_BIT(PORTB, PB7); 

	//send write instruction
	SPI_write(MCP_WRITE);
	
	//send address
	SPI_write(address);

	for(int i =0; i<num_bytes; ++i)
	{

		//send data
		SPI_write(data[i]);
	}
 	SET_BIT(PORTB, PB7); 


}

void MCP_request_to_send()
{
	
	CLEAR_BIT(PORTB, PB7); 

	SPI_write(MCP_RTS_TX0);

	SET_BIT(PORTB, PB7); 



}

uint8_t MCP_read_status()
{
	CLEAR_BIT(PORTB, PB7); 

	uint8_t result;

	

	SPI_write(MCP_READ_STATUS);

	result = SPI_read();

	SET_BIT(PORTB, PB7); 


	return result;

}

void MCP_bit_modify(uint8_t mask, uint8_t address, int8_t data)
{
	
	CLEAR_BIT(PORTB, PB7); 

	SPI_write(MCP_BITMOD);

	SPI_write(address);

	SPI_write(mask);

	SPI_write(data);

	SET_BIT(PORTB, PB7); 
}


void MCP_reset()
{
	CLEAR_BIT(PORTB, PB7); 

	SPI_write(MCP_RESET);

	SET_BIT(PORTB, PB7); 
}