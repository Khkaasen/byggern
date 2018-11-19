#ifndef buttons_h
#define buttons_h

#include <stdint.h>

typedef struct buttons_status
{
	int8_t right;
	int8_t left;
} buttons_struct;

int8_t read_left_button();
int8_t read_right_button();

buttons_struct get_buttons_status(void);

#endif