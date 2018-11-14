#ifndef menu_h
#define menu_h

#include <stdint.h>

typedef struct menu_struct
{
	uint8_t cursor_pos;
	uint8_t length;
	int position;

	

} menu_struct;


typedef struct menu_node_t
{
	struct menu_node_t * parent;
	struct menu_node_t * childs[3];
	char * title;
	int reallength;
} menu_node_t;

void menu_init();
void draw_cursor();
void delete_cursor();
void move_cursor();

#endif