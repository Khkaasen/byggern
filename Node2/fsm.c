#include "fsm.h"
#include "CAN_driver.h"
#include "IR_driver.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define GAME_OVER_ID 3

int state;

int change_state;

#define GAME_MODE 0

can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
};


void fsm_init()
{

	change_state = 0;

	state = IDLE; 

}


void fsm()
{

	float score =0;

	int8_t end_score;

	while(1){

		switch (state){

			case IDLE:

				while(1){

					_delay_ms(10); 

					if (msg_rec.id==2){  
						state = SET_UP;
						break; 
					}
				}
			case SET_UP:

				controller_select(msg_rec.data[GAME_MODE]);

				controller_init();				
				
				state= IN_GAME;

				break;

			case IN_GAME:

				score = 0;

				while(1){

					score+= 0.1; 

					if(msg_rec.id== 1){

						controller_set_motor_input(&msg_rec);

        				joystick_to_servopos(&msg_rec);

        				joystick_button_to_soleniode(&msg_rec);

						if(msg_rec.data[6]==1){

							state = GAME_OVER;
							break; 
						}
					}

					uint8_t block = detect_blockage();

					if (block==1){

						state = GAME_OVER;
						break;
					}
					_delay_ms(500);
				}

			case GAME_OVER: 

				end_score= score;

				int8_t byte[1]= {end_score};

				can_message msg_send=
			   	{
			       	.length=1,
			       	.id=GAME_OVER_ID,
			       	.RTR=0
			    };

			    msg_send.data[0] = byte[0];

			   	CAN_transmit(&msg_send);

			   	state = IDLE;

			   	break;
		}
	}
}

ISR(INT4_vect) {

  CAN_receive(&msg_rec);
}