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


can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
};



void fsm_init(){
	change_state = 0;

	state = IDLE; 

}


void fsm(){

	float score =0;
	int8_t end_score;

	while(1){

		switch (state){

			case IDLE:

				while(1){
					printf("idle\n\r");
					if (msg_rec.id==2){ // 2 er game_start_id fra node 1.  
						state = SET_UP;
						break; // vil brake while loop her.
					}
				}
			case SET_UP:
				printf("set up\r\n");

				controller_init();

				controller_select(msg_rec.data[0]); // her trenger jeg
				
				state= IN_GAME;

				break;

			case IN_GAME:
				printf("in game\r\n");

				score = 0;

				while(1){

					score+= 0.1; 

					if(msg_rec.id== 1){

						controller_set_motor_input(msg_rec);

        				joystick_to_servopos(msg_rec);

        				joystick_button_to_soleniode(msg_rec);


						if(msg_rec.data[6]==1){

							state = GAME_OVER;
							break; 
						}
					}
					uint8_t block = detect_blockage();

					if (detect_blockage()==1){
						state = GAME_OVER;
						break;
					}
					_delay_ms(500);
				}

			case GAME_OVER: 

				printf("game over\r\n");

				

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
/*
ISR(INT4_vect) {

  CAN_receive(&msg_rec);

}*/