#include "joystick_driver.h"
#include "PWM_driver.h"



#define MOTOR_GAIN 2.55
int motor_dir;

void joystick_to_servopos(can_message msg)
{
	if(msg.id==IO_ID)
	{
		PWM_set_duty_cycle(-msg.data[JOYSTICK_X]);
	}
	return;
}

uint8_t joystick_to_motorspeed (can_message msg)
{
	if(msg.id==IO_ID)
	{
		int8_t a = msg.data[JOYSTICK_X];
		uint8_t b= abs(a);
		uint8_t c = b* MOTOR_GAIN;
		return(c);
	}
}

int joystick_to_motordir(can_message msg)
{
	if(msg.id ==IO_ID)
	{
		if (msg.data[JOYSTICK_DIR]==1)
			motor_dir=1;
		if (msg.data[JOYSTICK_DIR]==3)
			motor_dir=0;
	}
	return motor_dir;
}

