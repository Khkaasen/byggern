#include "game.h"
#include "CAN_driver.h"
#include "motor_controller.h"
#include "joystick_driver.h"
#include "IR_driver.h"
#include "timer.h"

#include <stdio.h>
#include <stdint.h>

#define GAME_START_ID 2
#define GAME_INFO_ID 3
#define DUMMY_ID 10  

void game_start(can_message msg)
{
	if (msg.id == GAME_START_ID)
	{

		printf("game started node 2\n");
		controller_init();

		controller_select(msg.data[0]);

		/* denne added av marius*/
		//timer_start();

		game();	

	}

}

int8_t game_lost_handle(can_message msg)
{
	if (detect_blockage() || msg.data[6])

	//if for buttton to
	{
				//printf("bloacked detected or right button pushed\n");

		//read timer;
		//we have to check if timer larger than 128??  

		/* denne added av marius*/
		
		//int8_t score= timer_read_timer();
		int8_t score= 40;


		/* denne added av marius  */
		//timer_reset(); //tror ikke jeg trenger denne, siden den uansett blir satt til 0 når game starter. 

		int8_t b[2]= {1,score};
		 

		can_message msg=
    	{
        	.length=2,
        	.id=GAME_INFO_ID,
        	.RTR=0
    	};

    	msg.data[0] = b[0];
    	msg.data[1] = b[1];

   		CAN_transmit(&msg);


   				/* make sure last game_over message not still on can bus */

   		return(1);
	}
	else
	{
		int8_t b[2]= {0,0};
		 

		can_message msg=
    	{
        	.length=2,
        	.id=GAME_INFO_ID,
        	.RTR=0
    	};

    	msg.data[0] = b[0];
    	msg.data[1] = b[1];
   		CAN_transmit(&msg);
	}
	return 0;
}

void game()
{

	can_message msg;

    //int32_t ref;
	while(1)
	{
		printf("inside game while loop\n");

		CAN_receive(&msg);

    	controller_set_motor_input(msg);

        joystick_to_servopos(msg);

        joystick_button_to_soleniode(msg);

        if(msg.id == GAME_INFO_ID)
        {
			if(game_lost_handle(msg)==1)
	        {       		
	        	break;
	        }
        }
	        
	}
}
