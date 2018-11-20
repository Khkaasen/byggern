#include "fsm.h"
#define F_CPU 4915200UL
#include <util/delay.h>
#include "menu.h"
#include "game.h"
#include "joystick.h"
#include "sliders.h"
#include "CAN_driver.h"
#include "buttons.h"
#include <avr/interrupt.h>


change_of_state change_state; //denne er deklarert i h fil, tror ikke den trengs her. 

int state;

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

					if (change_state.game_mode >1){
						change_state.enable=1;
						
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

					//_delay_ms(10); //bytt ut denne med interrupt 
					//denne loopen skal ha ta 10 HZ!!!! 
					update_IO_card();

					transmit_IO_card(slider, joy, buttons);

					if (change_state.enable==1){
						state= GAME_OVER;
						break; //vil breake while loopen her. 
					}
				}

			case GAME_OVER:

				change_state.enable = 0;
				change_state.game_mode=0;

				uint8_t score= msg_rec.data[0]; // her må jeg få rett indeks på score som sendes fra node 2. definere score indeks?? 

				game_update_high_score(score);

				game_over(msg_rec.data[0], game_read_high_score()); //trenger rett indeks på score. hvor i data ligger den? 

				_delay_ms(5000);

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
