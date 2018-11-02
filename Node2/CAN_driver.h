#include <stdint.h>

typedef struct struct_can_message
{
	uint8_t id;
	uint8_t data[8];
	uint8_t length;
	uint8_t RTR;

} can_message;

void CAN_init();

void CAN_transmit(can_message msg);
can_message CAN_receive();

