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

#define LOWER_COL0 0x00
#define HIGHER_COL0 0x10

#define MENU_POS_LOW 0x0F
#define MENU_POS_HIGH 0x10

struct menu_struct menu;
bool shift_allowed;

struct menu_node_t* curr_menu;
struct menu_node_t main_menu;
struct menu_node_t singleplayer;
struct menu_node_t singleplayer_instructions;
struct menu_node_t teammode;
static const struct menu_node_t teammode_instructions;
struct menu_node_t highscores;
struct menu_node_t singleplayer_highscores;
struct menu_node_t teammode_highscores;
struct menu_node_t level_easy;
struct menu_node_t level_medium;
struct menu_node_t level_hard;
struct menu_node_t level_extreme;

 {
 	
 }; 


menu_node_t main_menu = 
{
	
	.title = "Main Menu",
	.parent = 0,
	.childs = {&singleplayer, &teammode, &highscores,NULL,NULL},
	.reallength = 3
};

menu_node_t singleplayer = 
{
	.title = "Singleplayer",
	.parent = &main_menu,
	.childs = {&singleplayer_instructions,&level_easy,&level_medium,&level_hard,&level_extreme},
	.reallength = 1	
};

menu_node_t teammode = 
{
	.title = "Teammode",
	.parent = &main_menu,
	.childs = {&teammode_instructions,&level_easy,&level_medium,&level_hard,&level_extreme},
	.reallength = 1		
};

menu_node_t singleplayer_instructions=
{
	.title = "Instructions",
	.parent = &singleplayer,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0	
};

static const menu_node_t teammode_instructions=
{
	.title = "Instructions",
	.parent = &teammode,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0
};

menu_node_t highscores =  
{
	.title = "Highscores",
	.parent = &main_menu,
	.childs = {&singleplayer_highscores,&teammode_highscores,NULL,NULL,NULL},
	.reallength = 2	
};

menu_node_t singleplayer_highscores = 
{
	.title = "S Highscores",
	.parent = &highscores,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0	
};

menu_node_t teammode_highscores =
{
	.title = "T Highscores",
	.parent = &highscores,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 0
};

menu_node_t level_easy =
{
	.title = "Level easy (PID)",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1
}

menu_node_t level_medium =
{
	.title = "Level medium (PD)",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1
}

menu_node_t level_hard =
{
	.title = "Level hard (P)",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1
}

menu_node_t level_extreme =
{
	.title = "Level extreme (mirror)",
	.parent = &main_menu,
	.childs = {NULL,NULL,NULL,NULL,NULL},
	.reallength = 1
}







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
	oled_print(">");
}

void delete_cursor()
{
	write_c(LOWER_COL0);
	write_c(HIGHER_COL0);
	write_c(menu.cursor_pos);
	for (uint8_t j = 0; j < 15; j++){
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

	if(menu.length==0)
	{
		delete_cursor();
		write_c(MENU_POS_LOW);
		write_c(MENU_POS_HIGH);
		line++;
		write_c(line);
		print_text_multiple_lines("hei, hallo, maen, eg e best, erik eie, han rule live");
	}
	for(int i= 0; i<node->reallength; i++)
	{
		write_c(MENU_POS_LOW);
		write_c(MENU_POS_HIGH);
		line++;
		write_c(line);
		oled_print((node->childs[i])->title);
	}
}

void print_text_multiple_lines(const char* string)
{
	uint8_t teller =0;
	uint8_t line = LINE1;
	write_c(MENU_POS_LOW);
	write_c(MENU_POS_HIGH);
	write_c(line);	
    char* stringPtr=string;
	while(*stringPtr !='\0')
	{
		teller++;
		oled_print_char_small(*stringPtr);
		if(teller>20 && *stringPtr ==' ' )
		{
			teller=0;
			write_c(MENU_POS_LOW);
			write_c(MENU_POS_HIGH);
			line++;
			write_c(line);
		}
		++stringPtr;
	}
}

void print_liten_telst(const char* string)
{
    char* stringPtr=string;
    int8_t teller = 0;

    while(*stringPtr != '\0'){
    	teller++;
        oled_print_char_small(*stringPtr);
        ++stringPtr;
        if(teller==127){
        	"\n";
        	stringPtr=0;
        }
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
				
				if(curr_menu->childs[menu.position]!=NULL)
				{
					delete_cursor();
					curr_menu = curr_menu->childs[menu.position];
					display_menu(curr_menu);
					
				}


				break;
			case 3: // left
				
				if(curr_menu->parent != NULL)
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


