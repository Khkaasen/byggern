#include "game.h"
#include "menu.h"
#include <stdint.h>
#include <stdio.h>


#define MODE_MENU 1
#define MODE_GAME 2
#define MODE_GAME_OVER 3 

static int mode;



void game_init()
{
	mode = MODE_MENU;
}


void game() 
{
	/* main game loop */
	while (1)
	{


		/* menu mode */

		while (mode == MODE_MENU)
		{
			
			mode = menu_change_menu();
			
		}

		/* game mode */
		while (mode ==MODE_GAME)
		{

		} 

	}
}