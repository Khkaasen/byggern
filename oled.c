#define F_CPU 4915200
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "oled.h"
#include "usbmultifunction.h"
#include "fonts.h"




volatile char* OLED_COMMAND = (char*) 0x1000;
volatile char* OLED_DATA = (char*) 0x1200; 
uint16_t OLED_DATA_SIZE= 0x200;

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
}

/*
void oled_print(char* )
{
    OLED_DATA[tall]= tall;
}
*/

void write_c(uint8_t command){
    *OLED_COMMAND = command;
}

void write_d(unsigned int data){
    *OLED_DATA=data;
}

void oled_reset()
{
    //OLED_DATA[0]=0xFF;
    //OLED_DATA[1]=0xFF;
    for (uint16_t i = 0xb0; i<=0xb8; i++){

        write_c(i);

        for (uint16_t j = 0; j < 128; j++){

        OLED_DATA[0]=0x00;
            
        }
    }       
}


void oledbajs(){
    write_c(0xb0);
    OLED_DATA[0]=0xFF;
}

void oled_print(char* b)
{
    int x = b;
    for (int i =0; i<4; i++){
            OLED_DATA[i]=font4[x][i];
    }

}
void print_test(){
    for (int i=1; i<8;i++){
        OLED_DATA[0]= font4[30][0];
    }
}