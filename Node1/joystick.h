#ifndef joystick_h
#define joystick_h

#include <stdint.h>

typedef enum 
{
	UP=0,
	RIGHT=1,
	DOWN=2,
	LEFT=3,
	NEUTRAL=4
} joystick_dir;

typedef struct joystick_status
{
	int8_t x;
	int8_t y;
	joystick_dir dir;
} joystick_status;

joystick_status get_joystick_status(void);

void transmit_joystick_status(joystick_status joystick);

#endif