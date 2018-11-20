#include "joystick_driver.h"
#include "PWM_driver.h"
#include <avr/io.h>


#define MOTOR_GAIN 2.55
int motor_dir;

void joystick_init()
{
	//set PC6 to output
	DDRC |= (1<<PC6);

	/* initailize PC6 to 1 */
	PORTC |= (1<<PC6);



}

void joystick_to_servopos(can_message * msg)
{
	if(msg->id==IO_ID)
	{
		printf("Joystick X: %d\n\r", msg->data[JOYSTICK_X] );
		PWM_set_duty_cycle(msg->data[JOYSTICK_X]);
	}
	return;
}

uint8_t joystick_to_motorspeed (can_message msg)
{
	if(msg.id==IO_ID)
	{
		int8_t a = msg.data[JOYSTICK_X];
		//printf("Joystick X: %d\n", a);
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

void joystick_button_to_soleniode(can_message msg)
{
	if(msg.id ==IO_ID)
	{
		printf("Joystick button: %d\n",msg.data[JOYSTICK_BUTTON] );
		if(msg.data[JOYSTICK_BUTTON]==1)
			PORTC |= (1<<PB6);
		else
			PORTC &= ~(1<<PB6);
	}
}