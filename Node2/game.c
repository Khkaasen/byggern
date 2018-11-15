#include "game.h"
#include "CAN_driver"
#include "sliders_driver.h"
#include "joystick_driver.h"
#include "IR_driver.h"

#include <stdio.h>
#include <stdint.h.h>

#define GAME_START_ID 2 

void game_start(can_message msg)
{
	if (msg.id == GAME_START_ID)
	{
		position_controller_init();

		game(msg.data[0]);
	}

}

void game(int8_t game_mode)
{
	/* switch choses correct game mode requeat sent from node 1 */
	


	while(1)
	{

	}
}
