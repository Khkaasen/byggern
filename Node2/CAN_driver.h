#ifndef CAN_COM_H_
#define CAN_COM_H_

#include <stdint.h>



typedef struct struct_can_message
{
	uint8_t id;
	int8_t data[8];
	uint8_t length;
	uint8_t RTR;

} can_message;

void CAN_init();

void CAN_receive(can_message * msg);

void CAN_transmit(can_message * msg);
#endif /* CAN_COM_H_ */
