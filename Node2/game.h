#ifndef game_h
#define game_h

#include "CAN_driver.h"

#include <stdint.h>

void game_start(can_message msg);

void game();

int8_t game_lost_handle(can_message msg); //return score 

#endif