#define F_CPU 4915200
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "oled.h"
#include "usbmultifunction.h"
#include <stdio.h>



volatile char* OLED_COMMAND = (char*) 0x1000;
volatile char* OLED_DATA = (char*) 0x1200; 


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
void oled_print(int tall)
{
    volatile char* oled = (char *) 0x1200; 
    oled[5]= tall;
}

void write_c(unsigned int command){
    *OLED_COMMAND = command;
}

void write_d(unsigned int data){
    *OLED_DATA=data;
}*/