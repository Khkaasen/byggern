#ifndef joystick_driver_h
#define joystick_driver_h


#include "CAN_driver.h"
#include <stdint.h>

#define JOYSTICK_X 0
#define JOYSTICK_Y 1
#define JOYSTICK_DIR 2
#define IO_ID 1

void joystick_to_servopos(can_message msg);

uint8_t joystick_to_motorspeed (can_message msg);


#endif