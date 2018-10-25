#include <stdint.h>

typedef struct struct_can_message
{
	uint8_t id;
	uint8_t *data;
	uint8_t length;
	uint8_t RTR;

} can_message;

void CAN_init();

void CAN_write(can_message msg);
can_message CAN_read();


