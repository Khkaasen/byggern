#define F_CPU 4915200UL

#include "game.h"
#include "menu.h"
#include "CAN_driver.h"
#include "sliders.h"
#include "joystick.h"
#include "buttons.h"
#include "oled.h"
#include "EEPROM_driver.h"

#include <stdint.h>
#include <stdio.h>
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
void game_over(uint8_t score, uint8_t high_score)
{

        oled_display_game_over(score,high_score);
        
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
        .id=GAME_START_ID,
        .RTR=0
    };

    msg.data[0] = b[0];

    // transmit can message to can 
    CAN_transmit(&msg);

}


void game_update_high_score(int score, int singel_or_team_mode){
    
    int high_single = EEPROM_read(0);

    int high_team = EEPROM_read(1);

    if (singel_or_team_mode==0 && score > high_single){
        EEPROM_write(0, score);
        return;
    }

    if (singel_or_team_mode ==1 && score > high_team){
        EEPROM_write(1, score);
        return;
    }

}

int game_read_high_score(int singel_or_team_mode){
    return EEPROM_read(singel_or_team_mode);
}















