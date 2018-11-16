#include "game.h"
#include "menu.h"
#include "CAN_driver.h"
#include "sliders.h"
#include "joystick.h"
#include "buttons.h"
#include <stdint.h>
#include <stdio.h>
#include "oled.h"

#define MODE_MENU 1
#define MODE_GAME 2
#define MODE_GAME_OVER 3 

#define GAME_START_ID 2

#define GAME_OVER_ID 3

#define PLAY 0
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
	can_message msg = CAN_read();

	if(msg.id== GAME_OVER_ID && msg.data[PLAY]==1)
	{
		return msg.data[SCORE];
	}
	return 0; 
}

void game_over(int8_t score)
{
	oled_display_game_over(score);

	/*save highscore in AVR
	//read all highscores 
	//print all highscores (top 10)
	
	
|	*/
}


void game(int8_t game_mode) 
{

	game_start(game_mode);

	printf("after game start()\n");

	joystick_struct joy;

    sliders_struct slider;

    buttons_struct buttons;

	/* game loop */
	while (1)
	{

     	joy = get_joystick_status();

      	slider = get_sliders_status();

      	buttons = get_buttons_status();

      	transmit_IO_card(slider, joy, buttons);

     	//_delay_ms(1);// needed? depends on implementation of CAN interrupt

     	/*if(game_check_game_over()>0)
     	{
     		game_over(game_check_game_over());
     		break; 
     	} */


     	/* DETTE SKAL BORT NÅR GAME OVER ER IMPLEMENTERT */
     	if(buttons.right==1)
     	{	
     		//her skal oled_print_game_quit() print "player quit the game. the score was ...."
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

    msg.data[PLAY] = b[PLAY];


    /* transmit can message to can */
    CAN_transmit(msg);

}

