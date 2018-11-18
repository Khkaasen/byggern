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

#define COUNTDOWN_POS_LOW 0x00 //må finne riktig verdi (dette skal være midten)
#define COUNTDOWN_POS_HIGH 0x14

#define PLAY_POS_LOW 0x00
#define PLAY_POS_HIGH 0x13

#define G_OVER_POS_LOW 0x00
#define G_OVER_POS_HIGH 0x12

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
    /* iterate all pages */
    for (uint8_t i = PAGE0; i<=PAGE7; i++){

        write_c(i);

        /* loop 128 times, wait for pointer to iterate all bytes. */
        for (uint8_t j = 0; j < 128; j++){

        	write_d(0x00);  //set all bytes to 0, this pointer increases by itself
            
        }
    }       
}


//KRØPLINGEN KOM SEG KUN HIT!!!!!!!!!!!!!

void oled_print_char(const char data)
{
    for (int i =0; i<8; i++)
    {
            write_d(pgm_read_byte(&font8[(int)data-32][i])); 
    }

}

void oled_print_number(uint8_t number)
{
    for (int i =0; i<8; i++)
    {                
        write_d(pgm_read_byte(&font8[number+16][i])); 
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

void oled_print_multiple_lines(const char* string)
{
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
        if(teller>20 && *stringPtr ==' ' )
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
        oled_reset();
        write_c(LINE4); //starte på linje
        write_c(COUNTDOWN_POS_LOW);
        write_c(COUNTDOWN_POS_HIGH);
        write_c(0x81); //akkseserer contrast
        write_c(0x00); //setter start verdi på contrast?
        oled_print_char(i); 
        for (uint16_t i=0x00; i<0xFF; i++ )
        {
            write_c(0x81); //akkseserer contrast
            write_c(i); //setter verdi på contrast?
            i+=0x04;
            _delay_ms(40);        
        }
    }
    
    oled_reset();
    write_c(LINE4); //starte på linje
    write_c(PLAY_POS_LOW);
    write_c(PLAY_POS_HIGH);
    write_c(0x81); //akkseserer contrast
    write_c(0xFF);
    oled_print("PLAY!");
}

/*
void oled_print_pic()
{
    uint8_t page = PAGE0;
    write_c(MENU_POS_LOW);
    write_c(MENU_POS_HIGH);

    for (int i =0; i<1024; i++)
    {
        if (i%128 == 0)
        {
            write_c(page);
            write_c(MENU_POS_LOW);
            write_c(MENU_POS_HIGH);
            page++; 
        }
        write_d(pgm_read_byte(&bitmap_iip07f[i]));
    }
}

*/

/* UNDER HER ER DET MYYYYEE KODE, BURDE KORTES NED */
void oled_display_game_over( uint8_t score , uint8_t high_score )
{
    oled_reset();
    /*Game Over!*/
    write_c(LINE2); //starte på linje
    write_c(G_OVER_POS_LOW);
    write_c(G_OVER_POS_HIGH);
    write_c(0x81); //akkseserer contrast
    write_c(0xFF); //full styrke
    oled_print("GAME OVER!");

    /* Score */
    uint8_t number_1 = 0;
    uint8_t number_2 = 0;
    uint8_t number_3 = 0;
    
    number_1 = score%10;
    number_2 = (score%100-number_1)/10;
    number_3 = (score%1000-number_2-number_1)/100;

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

/*
void oled_test_print()
{
    uint8_t number= 567;

    oled_print((char)(number));
}
*/