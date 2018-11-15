#include "buttons.h"
#include <stdio.h>
#include <avr/io.h>

int8_t read_left_button(){
    if (PINB & (1<<PB0)){
        return 1;
    }
    return 0;
}

int8_t read_right_button(){
    if (PINB & (1<<PB1)){
        return 1;
    }
    return 0;
}

buttons_struct get_buttons_status(void)
{
	buttons_struct value;

	value.right = read_right_button();

	value.left = read_left_button();

	return value;
}