#include "menu.h"
#include "oled.h"
#include "joystick.h"


uint8_t CURSOR_POS;
//menu_struct menu;
#define PAGE0 0xb0
#define PAGE1 0xb1
#define PAGE2 0xb2
#define PAGE3 0xb3
#define PAGE4 0xb4
#define PAGE5 0xb5
#define PAGE6 0xb6
#define PAGE7 0xb7


void menu_init()
{
	write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
	CURSOR_POS=PAGE0;
	//menu.cursor_pos=PAGE0;
	//menu.page=0;
	//write_c(menu.cursor:pos);
	write_c(CURSOR_POS);
	draw_cursor();
}

void draw_cursor()
{
	write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
	//write_c(menu.cursor_pos);
	write_c(CURSOR_POS);
	oled_print("->");
}

void delete_cursor()
{
	write_c(0x00);
	write_c(0x10);
	//write_c(menu.cursor_pos);
	write_c(CURSOR_POS);
	for (uint8_t j = 0; j < 16; j++){
        write_d(0x00);  //pekeren iterer av seg selv      
    }

}







void move_cursor()
{
	joystick_status joy = get_joystick_status();
	if(pos_max(joy))
	{
		switch(joy.dir)
		{
			case 0:
				delete_cursor();
				//menu.cursor_pos--;
				CURSOR_POS--;
				draw_cursor();
				break;
			case 2:
				delete_cursor();
				//menu.cursor_pos++;
				CURSOR_POS++;
				draw_cursor();
				break;
			default:
				break;
		}
	}


}


