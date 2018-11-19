#include "fsm.h"

#include "menu.h"
#include "game.h"
#include "joystick.h"
#include "slider.h"
#include <button.h>

#include <avr/interrupt.h>


int change_state; //denne er deklarert i h fil, tror ikke den trengs her. 

int state; 

  can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
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

		switch (STATE){

			case MENU:

				while (1){

					change_state.game_mode = menu_menu_change();

					if (state_change.game_mode >1){
						state_change.enable=1;
						
					}

					if(state_change.enable==1){
					state = IN_GAME;						
					}

					break;
				}

			case IN_GAME:
				
				change_state = 0;

				game_start(change_state.game_mode);

				while (1){
					//denne loopen skal ha ta 10 HZ!!!! 
					IO_card_update();

					transmit_IO_card(slider, joy, buttons);

					if (change_state.enable==1){
						state= GAME_OVER
						break; //vil breake while loopen her. 
					}
				}

			case GAME_OVER:

				change_state = 0;

				uint8_t score= msg_rec.data[0] // her må jeg få rett indeks på score som sendes fra node 2. definere score indeks?? 

				game_update_high_score(score);

				game_over(msg_rec.data[0], game_read_high_score()); //trenger rett indeks på score. hvor i data ligger den? 

				_delay_ms(5000)

				state= MENU;

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
