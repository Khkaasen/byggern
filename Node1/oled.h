#ifndef oled_h
#define oled_h

#include <stdint.h>

void oled_init();

void write_c(uint8_t command);

void write_d();

void oled_reset();

void oled_print_char(const char data);

void oled_print_number(uint8_t number); 

void oled_print(const char* string);

void oled_print_small(const char* string);

void oled_print_multiple_lines(const char* string);

void oled_display_countdown();

void oled_display_game_over(uint8_t score, uint8_t high_score);

#endif