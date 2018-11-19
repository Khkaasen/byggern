#define F_CPU 4915200UL
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


#define ENABLE 0xff
#define DISABLE 0x00

/* BITS */
#define RX0IF 0x00
#define RX0IE 0X01
#define RXM1_RXM0 0X60 

/* BUFFERS */
#define ID_HIGH_OFFSET 1
#define ID_LOW_OFFSET 2
#define DATA_LENGTH_OFFSET 5
#define DATA_BYTE_OFFSET 6

void CAN_init()
{	
	cli();

	MCP_init();
	_delay_ms(1);                                                         // HVORFOR DELAY
	
	/* Set can in config mode */
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
	_delay_ms(1);                                                         // HVOROFR DELAY

	/* Enable RX0IE interrupt */
	MCP_bit_modify(MCP_CANINTE, RX0IE, ENABLE);
	_delay_ms(1);                                                         // HVOROFR DELAY

	/* Disable the 3 last identifier bits*/
	MCP_bit_modify(MCP_TXB0CTRL+ID_LOW_OFFSET,MODE_MASK, DISABLE);

	/* Turn mask/filters off; receive any msg */
	MCP_bit_modify(MCP_RXB0CTRL,RXM1_RXM0,ENABLE);

	/* Set mode for CAN Controller */
  	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); 
	
	/* set interrupt on falling edge */
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);

	/* Set interrupt input to INT0 on Atmega162*/
	GICR |= (1<<INT0);  

	sei();	

}

void CAN_transmit(can_message * msg)
{	
	cli();

	/* Check if transmission is pending */
	while((MCP_read(MCP_TXB0CTRL)&(1<<TXREQ)))
	{	
		printf("Jeg er stuck i CAN_transmit");
	}
	
	/* Write id to register */
	MCP_write(msg->id,MCP_TXB0CTRL+ID_HIGH_OFFSET);

	/* Write lenght to register */
	MCP_bit_modify(MCP_TXB0CTRL+DATA_LENGTH_OFFSET,MASK_LENGTH,msg->length);

	/* Write data to register */
	MCP_write_n_bytes(MCP_TXB0CTRL+DATA_BYTE_OFFSET, msg->data,msg->length);

	/* SEND IT */
	MCP_request_to_send(); 

	sei();
}



void CAN_receive(can_message * msg) {
	
	/* Read ID */
	msg->id = MCP_read(MCP_RXB0CTRL+ID_HIGH_OFFSET);

	/* Read length and RTR*/
	uint8_t datalength = MCP_read(MCP_RXB0CTRL+DATA_LENGTH_OFFSET); //bytt ut 5 med define 

	/* Calculate length */
	msg->length = (MASK_LENGTH & datalength);
	
	/* Calculate RTR */
	msg->RTR = (MASK_RTR & datalength);

	/* Read data */
	MCP_read_n_bytes(MCP_RXB0CTRL+DATA_BYTE_OFFSET,msg->data,msg->length);

 	/* Clear recieve buffer full flag */
	MCP_bit_modify(MCP_CANINTF,(1 << RX0IF),DISABLE);

	return;
}



