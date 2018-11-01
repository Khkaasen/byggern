#include "menu.h"
#include "oled.h"
#include "joystick.h"
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

struct menu_struct menu;
bool shift_allowed;

struct menu_node_t* curr_menu;
struct menu_node_t main_menu;
struct menu_node_t singleplayer;
struct menu_node_t multiplayer;
struct menu_node_t registersingleplayer;


menu_node_t main_menu = 
{
	
	.title = "Main Menu",
	.parent = 0,
	.childs = {&singleplayer, &multiplayer},
	.reallength = 2
};

menu_node_t singleplayer = 
{
	.title = "Singleplayer",
	.parent = &main_menu,
	.childs = {&registersingleplayer,0},
	.reallength = 1		
};

menu_node_t multiplayer = 
{
	.title = "Multiplayer",
	.parent = &main_menu,
	.childs = {0,0},
	.reallength = 1		
};

menu_node_t registersingleplayer = 
{
	.title = "Register",
	.parent = &singleplayer,
	.childs = {0,0},
	.reallength = 1	
};






void menu_init()
{
	write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
	menu.cursor_pos=LINE1;
	menu.position = 0;
	//menu.length= main_menu.reallength;
	menu.length = singleplayer.reallength;
	write_c(menu.cursor_pos);
	draw_cursor();
	//curr_menu = &main_menu;
	curr_menu = &singleplayer;
	display_menu(curr_menu);
	shift_allowed = false;
}

void draw_cursor()
{
	write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
    write_c(menu.cursor_pos);
	oled_print("->");
}

void delete_cursor()
{
	write_c(0x00);
	write_c(0x10);
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
	for(int i= 0; i<node->reallength; i++)
	{
		write_c(0x0F);
		write_c(0x10);
		line++;
		write_c(line);
		oled_print((node->childs[i])->title);
	}
}



void move_cursor()
{

	joystick_status joy = get_joystick_status();
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
					menu.cursor_pos--;
					menu.position --;
				}
				draw_cursor();
				break;
			case 2: //down
				delete_cursor();
				if(menu.cursor_pos!=(TITLE+ menu.length))
				{
					menu.cursor_pos++;
					menu.position ++;
				}
				draw_cursor();
				break;
			case 1: // right
				
				if(curr_menu->childs[menu.position]!=0)
				{
					delete_cursor();
					curr_menu = curr_menu->childs[menu.position];
					display_menu(curr_menu);
					
				}


				break;
			case 3: // left
				
				if(curr_menu->parent != 0)
				{
					delete_cursor();
					curr_menu = curr_menu->parent;
					display_menu(curr_menu);
				}
				

				break;
			default:
				break;
		}
	}
}


