#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include "game.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define TITLE 0xb0
#define LINE1 0xb1
#define LINE2 0xb2
#define LINE3 0xb3
#define LINE4 0xb4
#define LINE5 0xb5
#define LINE6 0xb6
#define LAST_LINE 0xb7

#define LOWER_COL0 0x00
#define HIGHER_COL0 0x10

/* right adjust menu position to make space for cursor */
#define MENU_ADJUST_LOW 0x0F
#define MENU_ADJUST_HIGH 0x10

struct menu_struct menu;
bool shift_allowed;

static const struct menu_node_t* curr_menu;
static const struct menu_node_t main_menu;
static const struct menu_node_t singleplayer;
static const struct menu_node_t singleplayer_instructions;
static const struct menu_node_t teammode;
static const struct menu_node_t teammode_instructions;
static const struct menu_node_t highscores;
static const struct menu_node_t singleplayer_highscores;
static const struct menu_node_t teammode_highscores;
static const struct menu_node_t level_easy;
static const struct menu_node_t level_medium;
static const struct menu_node_t level_hard;
static const struct menu_node_t level_extreme;


static const menu_node_t main_menu = 
{
	
	.title = "Main Menu",
	.parent = 0,
	.childs = {&singleplayer, &teammode, &highscores,NULL,NULL},
	.reallength = 3,
	.mode = MODE_MENU
};

static const menu_node_t singleplayer = 
{
	.title = "Singleplayer",
	.parent = &main_menu,
	.childs = {&singleplayer_instructions,&level_easy,&level_medium,&level_hard,&level_extreme},
	.reallength = 5,
	.mode = MODE_MENU_SINGLE
};

static const menu_node_t teammode = 
{
	.title = "Teammode",
	.parent = &main_menu,
	.childs = {&teammode_instructions,&level_easy,&level_medium,&level_hard,&level_extreme},
	.reallength = 5,
	.mode = MODE_MENU_TEAM	
};

static const menu_node_t singleplayer_instructions=
{
	.title = "Instructions",
	.parent = &singleplayer,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT_S
};

static const menu_node_t teammode_instructions=
{
	.title = "Instructions",
	.parent = &teammode,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT_T
};

static const menu_node_t highscores =  
{
	.title = "Highscores",
	.parent = &main_menu,
	.childs = {&singleplayer_highscores,&teammode_highscores,NULL,NULL,NULL},
	.reallength = 2,
	.mode = MODE_MENU
};

static const menu_node_t singleplayer_highscores = 
{
	.title = "S Highscores",
	.parent = &highscores,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT 
};

static const menu_node_t teammode_highscores =
{
	.title = "T Highscores",
	.parent = &highscores,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT
};

static const menu_node_t level_easy =
{
	.title = "Level easy",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1,
	.mode = MODE_GAME_EASY
};

static const menu_node_t level_medium =
{
	.title = "Level medium",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1,
	.mode = MODE_GAME_MEDIUM
};

static const menu_node_t level_hard =
{
	.title = "Level hard",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1,
	.mode = MODE_GAME_HARD
};

static const menu_node_t level_extreme =
{
	.title = "Level extreme",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1,
	.mode = MODE_GAME_EXTREME
};



void menu_init()
{
	write_c(LOWER_COL0);	//set lower column to 0.
    write_c(HIGHER_COL0);	//set higher column to 0.
	menu.cursor_pos=LINE1; //cursor position at first option
	menu.position = 0;
	menu.length= main_menu.reallength; 	//set initial to main menu
	write_c(menu.cursor_pos);
	draw_cursor();
	curr_menu = &main_menu;
	display_menu(curr_menu);
	shift_allowed = false;
}

void draw_cursor()
{
	write_c(LOWER_COL0);	//set lower column to 0.
    write_c(HIGHER_COL0);	//set higher column to 0.
    write_c(menu.cursor_pos);
	oled_print("-");
}

void delete_cursor()
{
	write_c(LOWER_COL0);
	write_c(HIGHER_COL0);
	write_c(menu.cursor_pos);
	for (uint8_t j = 0; j < 15; j++){
        write_d(0x00);  //pointer iterates in hard ware     
    }

}

void display_menu(menu_node_t * node)
{
	oled_reset();
	menu.cursor_pos=LINE1;
	menu.position = 0;
	uint8_t line= TITLE;
	write_c(menu.cursor_pos);
	draw_cursor();
	menu.length = node->reallength;
	write_c(line);
	oled_print(node->title);

	/* handles Instrucion prints on oled */
	if(menu.length==0)
	{
		delete_cursor();
		write_c(MENU_ADJUST_LOW);
		write_c(MENU_ADJUST_HIGH);
		line++;
		write_c(line);

		if (node->mode==MODE_TEXT_S){
			oled_print_multiple_lines("Teller sekunder du klarer aa holde ballen i luften. Du styrer vinkel paa skuddet med joystick, og posisjon med venstre slider. LYKKE TIL! ");
		}
		if (node->mode==MODE_TEXT_T){
			oled_print_multiple_lines("Klare for samarbeid?? En spiller styrer vinkel paa skyter med joystick, men den andre styrer posisjonen med hoyre slider. LYKKE TIL!");
		}
	}

	for(int i= 0; i<node->reallength; i++)
	{
		write_c(MENU_ADJUST_LOW);
		write_c(MENU_ADJUST_HIGH);
		line++;
		write_c(line);
		oled_print((node->childs[i])->title);
	}
}

int game_type;

int menu_change_menu()
{	
	if (curr_menu->reallength==3 ){ // reset game_type if user in Main menu
		game_type =-1;
	}

	joystick_struct joy = get_joystick_status();
	if(joy.dir==4)
	{
		shift_allowed = true;
	}
	if(pos_max(joy)&&shift_allowed)
		{
		shift_allowed=false;
		switch(joy.dir)
		{
			case 0: //up
				delete_cursor();
				if(menu.cursor_pos!=LINE1)
				{
					menu.cursor_pos --;
					menu.position --;
				}
				draw_cursor();

				return 0;

			case 2: //down
				delete_cursor();
				if(menu.cursor_pos!=(TITLE+ menu.length))
				{
					menu.cursor_pos++;
					menu.position ++;
				}
				draw_cursor();

				return 0;

			case 1: // right
				
				if((curr_menu->childs[menu.position]!=NULL)) 
				{
					delete_cursor();

					curr_menu = curr_menu->childs[menu.position];

					if (curr_menu->mode ==MODE_MENU_SINGLE){
						game_type =0;
					}

					if (curr_menu->mode == MODE_MENU_TEAM){
						game_type =1;
					}

					if(curr_menu->mode >1)
					{	
						MODES mode = curr_menu->mode;

						curr_menu = curr_menu->parent;

						if (game_type ==0){
							return mode;
						}

						if (game_type==1){
							return mode * 10;
						}

					}


					if(curr_menu->mode ==1){
						
						display_menu(curr_menu); //text mode, print instruction on oled.
						curr_menu = curr_menu->parent;
						return 0;
					}


					display_menu(curr_menu);
				}
				return 0;

			case 3: // left
				
				if(curr_menu->parent != NULL)
				{
					delete_cursor();
					curr_menu = curr_menu->parent;
					display_menu(curr_menu);
				}
				
				return 0;

			default:

				return 0;
				
		}
	}
}


