#ifndef oled_h
#define oled_h

#include <stdint.h>

void init_oled();
void write_c(uint8_t command);
void write_d();


void oled_print_char(const char data);
void print_test();
void oled_print(const char* string);

#endif