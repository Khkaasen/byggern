#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include <avr/io.h>

void CAN_init()
{
	MCP_write(MODE_LOOPBACK,MCP_CANCTRL);

}