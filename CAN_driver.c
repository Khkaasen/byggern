#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include <avr/io.h>
#include "MCP2515.h"
#include <stdint.h>
#include <stdbool.h>

#define RXM0 5
#define TXREQ 3
void CAN_init()
{
	MCP_write(MODE_LOOPBACK,MCP_CANCTRL);
	MCP_write(0,MCP_TXB0CTRL+2);
	MCP_write(2<<RXM0,MCP_RXB0CTRL);
}

void CAN_write(can_message msg)
{
	//while(!(MCP_read(MCP_TXB0CTRL)&(1<<TXREQ)));



	uint8_t mask_length = 0x0F;
	uint8_t mask_RTR = 0x40;
	MCP_write(msg.id,MCP_TXB0CTRL + 1);
	MCP_bit_modify(mask_length,MCP_TXB0CTRL + 5,msg.length);
	MCP_bit_modify(mask_RTR,MCP_TXB0CTRL+5,msg.RTR);
	//MCP_write(TXB0CTRL + 5,msg->length); //hva skjer her?
	MCP_write_n_byte(msg.data, MCP_TXB0CTRL + 6, msg.length); //samme^

	MCP_request_to_send(); //set TXREQ bit
}

can_message CAN_read()
{
	while(!(MCP_read(MCP_CANINTF)&(1<<MCP_RX0IF)));

	can_message msg;
	msg.id = MCP_read(MCP_RXB0CTRL+1);
	uint8_t datalength = MCP_read(MCP_RXB0CTRL+5);
	msg.length = (0x0F && datalength);
	int j = 0;
	for(int i =6;i<msg.length;i++)
	{
		msg.data[j] = MCP_read(MCP_RXB0CTRL+i);
		j++;
	}
	msg.RTR = (0x40 && datalength);
	return msg;
}


