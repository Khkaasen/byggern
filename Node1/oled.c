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

#define TITLE 0xb0
#define LINE1 0xb1
#define LINE2 0xb2
#define LINE3 0xb3
#define LINE4 0xb4
#define LINE5 0xb5
#define LINE6 0xb6
#define LAST_LINE 0xb7

#define MENU_POS_LOW 0x0F
#define MENU_POS_HIGH 0x10

#define COUNTDOWN_POS_LOW 0x00
#define COUNTDOWN_POS_HIGH 0x14

#define PLAY_POS_LOW 0x00
#define PLAY_POS_HIGH 0x13

#define G_OVER_POS_LOW 0x00
#define G_OVER_POS_HIGH 0x12

#define DESABLE 0x00
#define ASCII_OFFSET 32
#define NUMBER_OFFSET 16
#define LARGE_FONT 8
#define SMALL_FONT 4
#define HORIZONTAL_PIXELS 128

#define CONTRAST_REGISTER 0x81
#define MIN_CONTRAST 0x00
#define MAX_CONTRAST 0xFF
#define INCREASE_CONTRAST 0x04


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

void write_c(uint8_t command)
{
    *OLED_COMMAND = command;
}

void write_d(unsigned int data)
{
    *OLED_DATA=data;
}

void oled_reset()
{
    /* iterate all pages */
    for (uint8_t i = PAGE0; i<=PAGE7; i++)
    {
        write_c(i);
        /* loop 128 times, wait for pointer to iterate all bytes. */
        for (uint8_t j = 0; j < HORIZONTAL_PIXELS; j++){
        	write_d(DESABLE);  //set all bytes to 0, this pointer increases by itself
        }
    }       
}

void oled_print_char(const char data)
{
    for (int i =0; i<LARGE_FONT; i++)
    {
        write_d(pgm_read_byte(&font8[(int)data - ASCII_OFFSET][i])); 
    }
}

void oled_print_number(uint8_t number)
{
    for (int i =0; i<LARGE_FONT; i++)
    {                
        write_d(pgm_read_byte(&font8[number + NUMBER_OFFSET][i])); 
    }    
}

void oled_print_char_small(const char data)
{
    for (int i=0; i<SMALL_FONT;i++)
        write_d(pgm_read_byte(&font4[(int)data - ASCII_OFFSET][i]));
}

void oled_print(const char* string)
{
	char* stringPtr=string;
	while(*stringPtr != '\0')
    {
		oled_print_char(*stringPtr);
		++stringPtr;
	}
}

void oled_print_small(const char* string)
{
    char* stringPtr=string;
    while(*stringPtr != '\0')
    {
        oled_print_char_small(*stringPtr);
        ++stringPtr;
    }
}

void oled_print_multiple_lines(const char* string)
{
    /* Set start point */
    uint8_t teller =0;
    uint8_t line = LINE1;
    write_c(MENU_POS_LOW);
    write_c(MENU_POS_HIGH);
    write_c(line);  
    char* stringPtr=string;
    while(*stringPtr !='\0')
    {
        teller++;
        oled_print_char_small(*stringPtr);

        /* New line */
        if(teller>20 && *stringPtr ==' ')
        {
            teller=0;
            write_c(MENU_POS_LOW);
            write_c(MENU_POS_HIGH);
            line++;
            write_c(line);
        }
        ++stringPtr;
    }
}

void oled_display_countdown()
{
    for(char i='3'; i>'0'; i--)
    {
        /* Set start point */
        oled_reset();
        write_c(LINE4);
        write_c(COUNTDOWN_POS_LOW);
        write_c(COUNTDOWN_POS_HIGH);

        /* Set contrast */
        write_c(CONTRAST_REGISTER);
        write_c(MIN_CONTRAST);
        oled_print_char(i); 
        /* Change contrast */
        for (uint16_t i=MIN_CONTRAST; i<MAX_CONTRAST; i++ )
        {
            write_c(CONTRAST_REGISTER);
            write_c(i);
            i+=INCREASE_CONTRAST;
            _delay_ms(40);        
        }
    }
    /* Set start point */
    oled_reset();
    write_c(LINE4);
    write_c(PLAY_POS_LOW);
    write_c(PLAY_POS_HIGH);
    /* Set contrast*/
    write_c(CONTRAST_REGISTER);
    write_c(MAX_CONTRAST);
    oled_print("PLAY!");
}

void oled_display_game_over( uint8_t score , uint8_t high_score )
{
    oled_reset();

    /*Game Over!*/
    write_c(LINE2); 
    write_c(G_OVER_POS_LOW);
    write_c(G_OVER_POS_HIGH);
    write_c(CONTRAST_REGISTER);
    write_c(MAX_CONTRAST);
    oled_print("GAME OVER!");

    /* Score */
    uint8_t number_1 = 0;
    uint8_t number_2 = 0;
    uint8_t number_3 = 0;
    
    number_1 = score%10;
    number_2 = (score%100-number_1)/10;
    number_3 = (score%1000-number_2-number_1)/100;

    /* Set start point*/
    write_c(LINE5); 
    write_c(MENU_POS_LOW);
    write_c(MENU_POS_HIGH);

    oled_print("Score: ");
    if(number_3!=0){
        oled_print_number(number_3);
    }
    if(number_2!=0 && number_3!=0){
        oled_print_number(number_2);
    }
    oled_print_number(number_1);

    /* Highscore */
    write_c(LINE6);
    write_c(MENU_POS_LOW);
    write_c(MENU_POS_HIGH);

    uint8_t number_4 = 0;
    uint8_t number_5= 0;
    uint8_t number_6 = 0;

    number_4 = high_score%10;
    number_5= (high_score%100-number_4)/10;
    number_6 = (high_score%1000-number_5-number_4)/100;

     oled_print("Best : ");
    if(number_6!=0){
        oled_print_number(number_6);
    }
    if(number_5!=0 && number_6!=0){
        oled_print_number(number_5);
    }
    oled_print_number(number_4);
}