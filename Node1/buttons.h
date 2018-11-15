#ifndef buttons_h
#define buttons_h

#include <stdint.h>

int8_t read_left_button();
int8_t read_right_button();


typedef struct buttons_status
{
	int8_t right;
	int8_t left;
} buttons_struct;

buttons_struct get_buttons_status(void);

#endif