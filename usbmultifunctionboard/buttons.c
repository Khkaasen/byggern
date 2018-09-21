#include "buttons.h"
#include <stdio.h>
#include <avr/io.h>

bool read_left_button(){
    if (PINB & (1<<PB0)){
        return true;
    }
}

bool read_right_button(){
    if (PINB & (1<<PB1)){
        return true;
    }
}