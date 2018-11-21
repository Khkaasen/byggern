#include "fsm.h"
#define F_CPU 4915200UL

#include "menu.h"
#include "game.h"
#include "joystick.h"
#include "sliders.h"
#include "CAN_driver.h"
#include "buttons.h"

#include <avr/interrupt.h>
#include <util/delay.h>


change_of_state change_state;

int state;

int singel_or_team_mode =-1;

can_message msg_rec = {
    .length=1,
    .id=1,
    .RTR=0
  };

joystick_struct joy;

sliders_struct slider;

buttons_struct buttons;

void update_IO_card(){

	    joy = get_joystick_status();
        
      	slider = get_sliders_status();
        
      	buttons = get_buttons_status();
}

void fsm_init(){

	change_state.enable=0;
	change_state.game_mode=0;

	state= MENU;

}

void fsm(){

	while(1){

		change_state.enable=0;
		change_state.game_mode=0;

		switch (state){

			case MENU:

				menu_init();

				while (1){

					change_state.game_mode = menu_change_menu();

					if (change_state.game_mode >1){ //handles game start in single mode 
						change_state.enable=1;
						singel_or_team_mode=0;	
					}

					if (change_state.game_mode > 10){ //handes game start in team mode 
						singel_or_team_mode =1;
						change_state.game_mode /=10;
					}

					if(change_state.enable==1){
					state = IN_GAME;
					break;						
					}
				}

			case IN_GAME:
				
				change_state.enable = 0;

				game_start(change_state.game_mode);

				while (1){
					_delay_ms(10);
					update_IO_card();

					/* this line should send 10 messages pr second */
					transmit_IO_card(slider, joy, buttons);

					if (change_state.enable==1){
						state= GAME_OVER;
						break;
					}
				}

			case GAME_OVER:

				change_state.enable = 0;
				change_state.game_mode=0;

				uint8_t score= msg_rec.data[0]; 

				game_update_high_score(score, singel_or_team_mode);

				game_over(msg_rec.data[0], game_read_high_score(singel_or_team_mode)); 

				_delay_ms(5000);

				singel_or_team_mode =-1;

				state = MENU;

				break;
		} 
	}	
}


/* handles message received ineterrupt */
ISR(INT0_vect)
{
  change_state.enable = 1; 
  CAN_receive(&msg_rec);

}
