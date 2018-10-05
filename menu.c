#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdbool.h>
#include <string.h>


menu_struct menu;
bool shift_allowed;


#define TITLE 0xb0
#define LINE1 0xb1
#define LINE2 0xb2
#define LINE3 0xb3
#define LINE4 0xb4
#define LINE5 0xb5
#define LINE6 0xb6
#define LAST_LINE 0xb7


void menu_init()
{
	write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
	menu.cursor_pos=LINE1;
	menu.length=0;
	write_c(menu.cursor_pos);
	draw_cursor();
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

void display_menu(char **menulist, int length)
{

	uint8_t line= TITLE;
	menu.length = length-1;
	/*if(len>7)
	{
		return;
	}
	*/
	for(int i= 0; i<length; i++)
	{
		write_c(0x0F);
		write_c(0x10);
		write_c(line);
		oled_print(menulist[i]);
		line++;
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
			case 0:
				delete_cursor();
				if(menu.cursor_pos!=LINE1)
				{
					menu.cursor_pos--;
				}
				draw_cursor();
				break;
			case 2:
				delete_cursor();
				if(menu.cursor_pos!=(TITLE+menu.length))
				{
					menu.cursor_pos++;
				}
				draw_cursor();
				break;
			default:
				break;
		}
	}


}


