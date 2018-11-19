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
	int8_t button; 
} joystick_struct;

joystick_struct get_joystick_status(void);

bool pos_max(joystick_struct joy);

void transmit_joystick_status(joystick_struct joystick);

#endif