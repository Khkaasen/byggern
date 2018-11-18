#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include "MCP2515.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RXM0 5
#define TXREQ 3
#define MASK_LENGTH 0x0F
#define MASK_RTR 0x40
#define MCP_RX0IE 0x00
void CAN_init()
{	
	printf("jeg er i can init\n");
	cli();

	/* set interrupt on falling edge */
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);

	GICR |= (1<<INT0);

	sei();	

	MCP_init();

	_delay_ms(1);
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG); //set can in config mode
	_delay_ms(1);

	MCP_bit_modify(MCP_CANINTE, 0x01, 1); //enabe rx0ie interrupt

	//MCP_bit_modify(MCP_RXB0CTRL, 0x04, 0x00); // Disable rollover

	_delay_ms(1);

	MCP_bit_modify(MCP_TXB0CTRL+2,MODE_MASK,0x00);

	MCP_bit_modify(0x60,MCP_RXB0CTRL,0xff); //Turn mask/filters off; receive any msg

  	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // Set mode for CAN Controller.

}

void CAN_transmit(can_message * msg)
{
	while((MCP_read(MCP_TXB0CTRL)&(1<<TXREQ)))
		;


	/* write id to register */
	MCP_write(msg->id,MCP_TXB0CTRL + 1);

	MCP_bit_modify(0xE0,MCP_TXB0CTRL + 2,0 );

	/* write lenght to register */
	MCP_bit_modify(MASK_LENGTH,MCP_TXB0CTRL + 5,msg->length); //hvordan setter vi lentgh her? setter antall bytes med 4 posisjoner. mens vi sender inn et heltall

	printf("id: %d ",msg->id);
	printf("data[0] %d\n\r",msg->data[0]);
	
	//MCP_bit_modify(MASK_RTR,MCP_TXB0CTRL+5,msg.RTR);
	//MCP_write(TXB0CTRL + 5,msg->length); //hva skjer her? skal vi ikke skrive på -> måten

	for (uint8_t i = 0; i< msg->length; i++) {
		MCP_write(msg->data[i], MCP_TXB0D0 + i);
	}


	MCP_request_to_send(); 

}



void CAN_receive(can_message * msg) {
	
	/*
	 if (!(MCP_read(MCP_CANINTF) & (1 << 0))) {
		return;
	}
	*/
	msg->id = MCP_read(MCP_RXB0CTRL+1);


	uint8_t datalength = MCP_read(MCP_RXB0CTRL+5); //bytt ut 5 med define 
	//printf("length read = 1: ");
	//printf("%x\n", MCP_read(MCP_RXB0CTRL+5));

	msg->length = (MASK_LENGTH & datalength);
	

	msg->RTR = (MASK_RTR & datalength);

	for (unsigned int i = 0; i < msg->length; i++) {
		msg->data[i] = (MCP_read(MCP_RXB0D0 + i));
	}
	//MCP_read_n_byte(msg.data,MCP_RXB0CTRL+6,msg.length);


 	//clear RX0IF flag
	MCP_bit_modify(MCP_CANINTF,(1 << 0),0);
	return;
}



