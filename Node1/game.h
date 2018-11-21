#ifndef game_h
#define game_h

#include <stdint.h>

void game_start(int8_t game_mode);

int8_t game_check_game_over();

void game_over(uint8_t score, uint8_t high_score);

void transmit_start_game(int8_t game_mode);

void game_update_high_score(int score, int singel_or_team_mode);

int game_read_high_score(int singel_or_team_mode);
#endif