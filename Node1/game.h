#ifndef game_h
#define game_h

#include <stdint.h>

void game_start(int8_t game_mode);

int8_t game_check_game_over();
void game_over(uint8_t score, uint8_t high_score);
void game(int8_t game_mode); 
void transmit_start_game(int8_t game_mode);

#endif