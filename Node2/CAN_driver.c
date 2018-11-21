#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "MCP2515.h"
#include "uart.h"
#include "MCP_driver.h"
#include "CAN_driver.h"

#define RXM0 5
#define TXREQ 3
#define MASK_LENGTH 0x0F
#define MASK_RTR 0x40
#define MCP_RX0IE 0x00


void CAN_init() {

	cli();

	MCP_init();

	_delay_ms(1);
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG); // Set mode for CAN Controller.
	_delay_ms(1);

	MCP_bit_modify(MCP_CANINTE, 0x01, 0xff); //enabe rx0ie interrupt

  	_delay_ms(1);

  	MCP_bit_modify(MCP_TXB0CTRL+2,MODE_MASK,0x00);  // set unused id bits 0 

	
  	MCP_bit_modify(MCP_RXB0CTRL,0x60,0xff); //Turn mask/filters off; receive any msg

  	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // Set mode for CAN Controller.


  	/* set up interrupt on Arduino */
	
    EICRB |= (1 << 1); // Set ISC41 to 1. Trigger INT4 On falling edge.
    EIMSK |= (1 << INT4); // External Interrupt Mask Register
  	
  	sei();

}



void CAN_receive(can_message * msg) {
	
	msg->id = MCP_read(MCP_RXB0CTRL+1);

	uint8_t datalength = MCP_read(MCP_RXB0CTRL+5); //bytt ut 5 med define 

	msg->length = (MASK_LENGTH & datalength);
	
	msg->RTR = (MASK_RTR & datalength);

	MCP_read_n_bytes(MCP_RXB0CTRL+6,msg->data,msg->length);

 	//clear RX0IF flag
	MCP_bit_modify(MCP_CANINTF,(1 << 0),0);

	return;
}


void CAN_transmit(can_message * msg)
{
	cli();

	while((MCP_read(MCP_TXB0CTRL)&(1<<TXREQ)))
		;

	/* write id to register */
	MCP_write(msg->id,MCP_TXB0CTRL + 1);

	/* write lenght to register */
	MCP_bit_modify(MCP_TXB0CTRL + 5,MASK_LENGTH,msg->length);

	MCP_write_n_bytes(MCP_TXB0CTRL+6, msg->data,msg->length);

	MCP_request_to_send(); 
	
	sei();
}
