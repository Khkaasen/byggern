#ifndef slider_driver_h
#define slider_driver_h 


#include <stdint.h>

#include "CAN_driver.h"

#define SLIDER_LEFT 4
#define SLIDER_RIGHT 5
#define IO_ID 1

void controller_select(int8_t game_mode);

void controller_init();

int32_t controller_read_motor_ref(can_message * msg);

void controller_set_motor_input(can_message * msg);


#endif