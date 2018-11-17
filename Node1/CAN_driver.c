#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include "MCP2515.h"
#include <stdint.h>
#include <stdbool.h>

#define RXM0 5
#define TXREQ 3
#define MASK_LENGTH 0x0F
#define MASK_RTR 0x40
#define MCP_RX0IE 0x00
void CAN_init()
{	
	/*  */
	MCP_write(0xff,MCP_CANINTE);

	MCP_write(0x00,MCP_CANINTF);

	MCP_reset();

	MCP_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_CONFIG);
	if (MCP_read(MCP_CANSTAT) & MODE_MASK != MODE_CONFIG) {
		//printf("Not in config mode\n");
	}

	/* enable interrupt for message recieved. then set to 1 */
	MCP_bit_modify(MCP_CANINTE, (1 << MCP_RX0IE), 1);

	MCP_bit_modify(MCP_CANINTF, (1 << MCP_RX0IF), 0);

	MCP_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_NORMAL); //set CAN to normal mode.
}

void CAN_transmit(can_message msg)
{
	while((MCP_read(MCP_TXB0CTRL)&(1<<TXREQ))); 

	/* write id to register */
	MCP_write(msg.id,MCP_TXB0CTRL + 1);

	MCP_bit_modify(0xE0,MCP_TXB0CTRL + 2,0 );

	/* write lenght to register */
	MCP_bit_modify(MASK_LENGTH,MCP_TXB0CTRL + 5,msg.length); //hvordan setter vi lentgh her? setter antall bytes med 4 posisjoner. mens vi sender inn et heltall

	//MCP_bit_modify(MASK_RTR,MCP_TXB0CTRL+5,msg.RTR);
	//MCP_write(TXB0CTRL + 5,msg->length); //hva skjer her? skal vi ikke skrive på -> måten

	MCP_write_n_byte(msg.data, MCP_TXB0CTRL + 6, msg.length); //samme^


	MCP_request_to_send(); 


}

can_message CAN_receive()
{

	while(!(MCP_read(MCP_CANINTF)&(1<<MCP_RX0IF))) {
		;
	};	
	can_message msg;
	msg.id = MCP_read(MCP_RXB0CTRL+1);
	uint8_t datalength = MCP_read(MCP_RXB0CTRL+5); //bytt ut 5 med define 
	//printf("length read = 1: ");
	//printf("%x\n", MCP_read(MCP_RXB0CTRL+5));
	msg.length = (MASK_LENGTH & datalength);
	
	msg.RTR = (MASK_RTR & datalength);


	MCP_read_n_byte(msg.data,MCP_RXB0CTRL+6,msg.length);


	MCP_bit_modify((1 << MCP_RX0IF), MCP_CANINTF,0); //clear bit


	return msg;
}


