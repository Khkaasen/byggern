#include "usbmultifunction.h"
#include "joystick.h"
#include <stdio.h>

#define CHANNEL_X 4  //CHANNEL 1
#define CHANNEL_Y 5  //CHANNEL 2
 



joystick_status get_joystick_status()
{

	struct joystick_status joystick;

	joystick.x = read_channel(CHANNEL_X);
	printf("Joystick X:pos %4u  ", joystick.x);
	joystick.y = read_channel(CHANNEL_Y);
	printf("Joystick Y:pos %4u \n", joystick.y);
	joystick.dir = 0;
	return joystick;
}
