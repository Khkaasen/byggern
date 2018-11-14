#define F_CPU 4915200
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "oled.h"
#include "usbmultifunction.h"
#include "fonts.h"




volatile char* OLED_COMMAND = (char*) 0x1000;
volatile char* OLED_DATA = (char*) 0x1200; 
uint16_t OLED_DATA_SIZE= 0x200;

#define PAGE0 0xb0
#define PAGE1 0xb1
#define PAGE2 0xb2
#define PAGE3 0xb3
#define PAGE4 0xb4
#define PAGE5 0xb5
#define PAGE6 0xb6
#define PAGE7 0xb7


void oled_init()
{
    write_c(0xae);  //display off
    write_c(0xa1);  //segment remap
    write_c(0xda);  //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8);  //common output scan direction:com63~com0
    write_c(0xa8);  //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5);  //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81);  //contrast control
    write_c(0x50);
    write_c(0xd9);  //set pre-charge period
    write_c(0x21);
    write_c(0x20);  //set memory adressing mode
    write_c(0x02); 
    write_c(0xdb);  //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad);  //master configuration
    write_c(0x00);
    write_c(0xa4);  //out follows RAM content
    write_c(0xa6);  //set normal display
    write_c(0xaf);  //display on
    write_c(PAGE0);	//set page start page 0.
    write_c(0x00);	//set lower column to 0.
    write_c(0x10);	//set higher column to 0.
}


void write_c(uint8_t command){
    *OLED_COMMAND = command;
}

void write_d(unsigned int data){
    *OLED_DATA=data;
}

void oled_reset()
{
    for (uint8_t i = PAGE0; i<=PAGE7; i++){

        write_c(i);

        for (uint8_t j = 0; j < 128; j++){

        	write_d(0x00);  //pekeren iterer av seg selv
            
        }
    }       
}


void oled_print_char(const char data)
{
    for (int i =0; i<8; i++){
            write_d(pgm_read_byte(&font8[(int)data-32][i]));
    }

}
void oled_print_char_small(const char data)
{
    for (int i=0; i<4;i++)
        write_d(pgm_read_byte(&font4[(int)data-32][i]));
}

void oled_print(const char* string){
	char* stringPtr=string;
	while(*stringPtr != '\0'){
		oled_print_char(*stringPtr);
		++stringPtr;
	}
}

void oled_print_small(const char* string)
{
    char* stringPtr=string;
    while(*stringPtr != '\0'){
        oled_print_char_small(*stringPtr);
        ++stringPtr;
    }
}

void set_start_col(int col)
{
    if(col>128 || col<0)
    {
        return;
    }

}
