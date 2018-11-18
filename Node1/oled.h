#ifndef oled_h
#define oled_h

#include <stdint.h>

void init_oled();  //denne skal hete oled_init()

void write_c(uint8_t command);

void write_d();

void oled_print_char(const char data);

void oled_print_number(uint8_t number); 

void print_test();

void oled_print(const char* string);

void oled_print_multiple_lines(const char* string);

void oled_display_countdown();

//void oled_print_pic();

void oled_display_game_over(uint8_t score, uint8_t high_score);
/*
void oled_test_print();
*/

#endif