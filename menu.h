#include <stdint.h>

typedef struct menu_struct
{
	uint8_t cursor_pos;
	uint8_t length;

} menu_struct;


typedef struct menu_node_t
{
	struct menu_node_t * parent;
	struct menu_node_t * childs[2];
	char * title;
	int reallength;
} menu_node_t;

void menu_init();
void draw_cursor();
void delete_cursor();
void move_cursor();
