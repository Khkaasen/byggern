#include "game.h"
#include "CAN_driver.h"
#include "motor_controller.h"
#include "joystick_driver.h"
#include "IR_driver.h"

#include <stdio.h>
#include <stdint.h>

#define GAME_START_ID 2 

void game_start(can_message msg)
{
	if (msg.id == GAME_START_ID)
	{
		controller_init();

		controller_select(msg.data[0]);

		game();	
	}

}

void game()
{

	can_message msg;

    int32_t ref;
	while(1)
	{
		msg=CAN_receive();

    	ref =controller_read_motor_ref(msg);

    	controller_set_motor_input(ref);

        joystick_to_servopos(msg);

        joystick_button_to_soleniode(msg);

	}
}
