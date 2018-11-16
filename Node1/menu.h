#ifndef menu_h
#define menu_h

#include <stdint.h>


typedef enum 
{
	MODE_MENU=0,
	MODE_GAME_EASY=1,
	MODE_GAME_MEDIUM= 2,
	MODE_GAME_HARD= 3,
	MODE_GAME_EXTREME =4,
	MODE_TEXT = 5	
} MODES;


typedef struct menu_struct
{
	uint8_t cursor_pos;
	uint8_t length;
	int position;

} menu_struct;

typedef struct menu_node_t
{
	struct menu_node_t * parent;
	struct menu_node_t * childs[5];
	char * title;
	int reallength;
	MODES mode;
} menu_node_t;

void menu_init();
void draw_cursor();
void delete_cursor();
void menu_change_menu();

#endif