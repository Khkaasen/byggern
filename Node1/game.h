#ifndef game_h
#define game_h

#include <stdint.h>

void game_start();

int8_t game_check_game_over();
void game_over(int8_t score);
void game(); 
void transmit_start_game();

#endif