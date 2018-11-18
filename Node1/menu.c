#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "game.h"

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
	.mode = MODE_MENU
};

static const menu_node_t teammode = 
{
	.title = "Teammode",
	.parent = &main_menu,
	.childs = {&teammode_instructions,&level_easy,&level_medium,&level_hard,&level_extreme},
	.reallength = 5,
	.mode = MODE_MENU	
};

static const menu_node_t singleplayer_instructions=
{
	.title = "Instructions",
	.parent = &singleplayer,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT
};

static const menu_node_t teammode_instructions=
{
	.title = "Instructions",
	.parent = &teammode,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0,
	.mode = MODE_TEXT
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
	.mode = MODE_MENU
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
	oled_print("->");
}

void delete_cursor()
{
	write_c(LOWER_COL0);
	write_c(HIGHER_COL0);
	write_c(menu.cursor_pos);
	for (uint8_t j = 0; j < 16; j++){
        write_d(0x00);  //pekeren iterer av seg selv      
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

	printf("menu: %s\n", node->title);

	if(menu.length==0)
	{
		delete_cursor();
		write_c(MENU_ADJUST_LOW);
		write_c(MENU_ADJUST_HIGH);
		line++;
		write_c(line);
		oled_print_multiple_lines("Teller sekunder du klarer å holde ballen i luften. Du styrer servo med joystick, og posisjon med venstre slider. LYKKE TIL! ");
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



void menu_change_menu()
{
	printf("start of menu\n");
	joystick_struct joy = get_joystick_status();
	printf("joystick.dir: %d\n", joy.dir);
	if(joy.dir==4)
	{
		shift_allowed = true;
		printf("1\n");
	}
	if(pos_max(joy)&&shift_allowed)
	{
		printf("2\n");
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
				printf("up\n");
				break;
			case 2: //down
				delete_cursor();
				if(menu.cursor_pos!=(TITLE+ menu.length))
				{
					menu.cursor_pos++;
					menu.position ++;
				}
				draw_cursor();
				printf("down\n");
				break;
			case 1: // right
				
				if((curr_menu->childs[menu.position]!=NULL)) //check if menu.child is game mode 
				{
					delete_cursor();
					curr_menu = curr_menu->childs[menu.position];
					if(curr_menu->mode >0)
					{	
						printf("right + game\n");
						game(curr_menu->mode);
						curr_menu = curr_menu->parent;
					}
					display_menu(curr_menu);
					printf("right\n");	
				}
				break;
			case 3: // left
				
				if(curr_menu->parent != NULL)
				{
					delete_cursor();
					curr_menu = curr_menu->parent;
					display_menu(curr_menu);
					printf("left\n");
				}
				
				break;
			default:
				break;
		}
	}
}


