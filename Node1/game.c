#define F_CPU 4915200UL

#include "game.h"
#include "menu.h"
#include "CAN_driver.h"
#include "sliders.h"
#include "joystick.h"
#include "buttons.h"
#include <stdint.h>
#include <stdio.h>
#include "oled.h"
#include <avr/interrupt.h>

#include <util/delay.h>

#define MODE_MENU 1
#define MODE_GAME 2
#define MODE_GAME_OVER 3 

#define GAME_START_ID 2

#define GAME_INFO_ID 3

#define SCORE 1

#define MESSAGE_LENGTH 1

static int mode;





void game_start(int8_t game_mode)
{

	transmit_start_game(game_mode);

	oled_display_countdown();

	
}


int8_t game_check_game_over()
{   
	can_message msg;

    
	if(msg.id== GAME_INFO_ID && msg.data[0]!=0)
	{
        int8_t score = msg.data[1];
		return score;
	}
    
	return 0; 
}
void game_over(uint8_t score,uint8_t high_score)
{
        oled_display_game_over(score,high_score);

        //save highscore in AVR

        //read all highscores 
        //print all highscores (top 10)
        
}


void game(int8_t game_mode) 
{

	game_start(game_mode);

	joystick_struct joy;

    sliders_struct slider;

    buttons_struct buttons;

    can_message msg;

	// game loop
	while (1)
	{


     	joy = get_joystick_status();

        
      	slider = get_sliders_status();
        
      	buttons = get_buttons_status();
        

      	transmit_IO_card(slider, joy, buttons);

        
        can_message msg = 
        {
            .length = 2,
            .id = GAME_INFO_ID,
            .RTR = 0

        };
        int8_t b[2]= {0,0};

        msg.data[0] = b[0];
        msg.data[1] = b[1];
        
        CAN_transmit(&msg);


     	//_delay_ms(1);// needed? depends on implementation of CAN interrupt



        uint8_t score = game_check_game_over();
        uint8_t high_score = 96; //randomshit

        //printf("%d\n",game_over);
        if (score!=0)
        {

            game_over(score, high_score);

            _delay_ms(3000);
            break;
        }


        
	}
}


void transmit_start_game(int8_t game_mode)
{
	int8_t b[MESSAGE_LENGTH] = 
	{	
		game_mode
	};

    can_message msg=
    {
        .length=MESSAGE_LENGTH,
        .id=GAME_START_ID, //id = 2 is GAME_START_ID
        .RTR=0
    };

    msg.data[0] = b[0];


    // transmit can message to can 
    CAN_transmit(&msg);

}

