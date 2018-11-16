#include "game.h"
#include "CAN_driver.h"
#include "motor_controller.h"
#include "joystick_driver.h"
#include "IR_driver.h"

#include <stdio.h>
#include <stdint.h>

#define GAME_START_ID 2
#define GAME_OVER_ID 3  

void game_start(can_message msg)
{
	if (msg.id == GAME_START_ID)
	{
		printf("inside game_start\n");
		controller_init();

		controller_select(msg.data[0]);

		game();	

		//timer for score må startes her. 
	}

}

int8_t game_lost_handle(can_message msg)
{
	if (detect_blockage() || msg.data[6])
	//if for buttton to
	{

		//read timer;
		//we have to check if timer larger than 128??  
		int8_t score=40;
		//stop or reset timer; 

		int8_t b[1]= {0};
		b[0]= score; //denne skal countes opp hit. 

		can_message msg=
    	{
        	.length=1,
        	.id=GAME_OVER_ID,
        	.RTR=0
    	};

   		CAN_transmit(msg);

   		printf("hælla");
   		return(1);

		//break; //want to break while loop 
	}
}

void game()
{

	can_message msg;

    int32_t ref;
	while(1)
	{
		printf("inside game while\n");

		msg=CAN_receive();

    	ref =controller_read_motor_ref(msg);

    	controller_set_motor_input(ref);

        joystick_to_servopos(msg);

        joystick_button_to_soleniode(msg);

        if(game_lost_handle(msg)==1)
        	break;
	}
}
