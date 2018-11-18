/*
 * mcp_com.c
 *
 * Created: 19.10.2018 14:16:21
 *  Author: margronv
 */ 

#include <avr/io.h>
#include "MCP2515.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"

void MCP_init() {
	SPI_init();
	MCP_reset();
}

void MCP_bit_modify(char address, char mask, char data) {
	PORTB &= ~(1 << PB4);

	SPI_write(MCP_BITMOD);

	SPI_write(address);

	SPI_write(mask);

	SPI_write(data);

	PORTB |= (1 << PB4);
}


void MCP_reset() {
	PORTB &= ~(1 << PB4);
	SPI_write(MCP_RESET);
	PORTB |= (1 << PB4);
}



char MCP_read(char address) {
	
	PORTB &= ~(1 << PB4);

	uint8_t result;

	//select CAN-controller
	

	//send read instrucion
	SPI_write(MCP_READ);

	//send address
	SPI_write(address);

	//read result
	result = SPI_read();

	PORTB |= (1 << PB4);
	
	return result;
}

void MCP_write(int8_t data, uint8_t address) {
	PORTB &= ~(1 << PB4);

	//send write instruction
	SPI_write(MCP_WRITE);

	//send address
	SPI_write(address);

	//send data
	SPI_write(data);


	PORTB |= (1 << PB4);
}

void MCP_request_to_send() {
	PORTB &= ~(1 << PB4);
	
	SPI_write(MCP_RTS_TX0);
	

	PORTB |= (1 << PB4);
}

uint8_t MCP_read_status() {
	PORTB &= ~(1 << PB4);

	uint8_t result;


	SPI_write(MCP_READ_STATUS);

	result = SPI_read();
	PORTB |= (1 << PB4);
	return result;
}