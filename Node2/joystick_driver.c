#include "joystick_driver.h"
#include "PWM_driver.h"


void joystick_to_servopos(can_message msg)
{
	if(msg.id==1)
	{
		PWM_set_duty_cycle(msg.data[1]);
	}
	return;
}

