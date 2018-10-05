#include <stdint.h>

typedef struct menu_struct
{
	uint8_t cursor_pos;
	uint8_t page;
} menu_struct;

void menu_init();
void draw_cursor();
void delete_cursor();
void move_cursor();