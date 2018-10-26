#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include "MCP2515.h"
#include <stdint.h>
#include <stdbool.h>

#define RXM0 5
#define TXREQ 3
void CAN_init()
{
	MCP_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_LOOPBACK); //bit modify og okke write
	MCP_bit_modify(MODE_MASK,MCP_TXB0CTRL+2,0x0);
	MCP_bit_modify(0x60,MCP_RXB0CTRL,0xff);
	MCP_write(0xff,MCP_CANINTE);
}

void CAN_write(can_message msg)
{
	//while(!(MCP_read(MCP_TXB0CTRL)&(1<<TXREQ)));

	uint8_t mask_length = 0x0F;
	uint8_t mask_RTR = 0x40;
	MCP_write(msg.id,MCP_TXB0CTRL + 1);
	MCP_bit_modify(mask_length,MCP_TXB0CTRL + 5,msg.length); //hvordan setter vi lentgh her? setter antall bytes med 4 posisjoner. mens vi sender inn et heltall
	printf("length write inni = 1: ");
	printf("%x\n", MCP_read(0x35));
	//MCP_bit_modify(mask_RTR,MCP_TXB0CTRL+5,msg.RTR);
	//MCP_write(TXB0CTRL + 5,msg->length); //hva skjer her? skal vi ikke skrive på -> måten
	MCP_write_n_byte(msg.data, MCP_TXB0CTRL + 6, msg.length); //samme^
	//printf("data: ");
	//printf("%x\n", MCP_read(0x36));

	MCP_request_to_send(); //set TXREQ bit  //må være feil her, mottar nada i recieve buffer
}

can_message CAN_read()
{

	/*while(!(MCP_read(MCP_CANINTF)&(1<<MCP_RX0IF)))
	{
		//teeeeeesssst
		printf("flags: ");
		printf("%x\n", MCP_read(MCP_CANINTF));
		//teeeeesssst

	}*/

	can_message msg;
	msg.id = MCP_read(MCP_RXB0CTRL+1);
	printf("Id = 5: ");
	printf("%x\n", MCP_read(MCP_RXB0CTRL+1));
	uint8_t datalength = MCP_read(MCP_RXB0CTRL+5);
	//printf("length read = 1: ");
	//printf("%x\n", MCP_read(MCP_RXB0CTRL+5));
	msg.length = (0x0F & datalength);
	int j = 0;
	for(int i =6;i<msg.length;i++)
	{
		msg.data[j] = MCP_read(MCP_RXB0CTRL+i);
		j++;
	}

	msg.RTR = (0x40 && datalength);
	return msg;
}


