#define F_CPU 4915200UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "sram.h"
#include "joystick.h"
#include "buttons.h"
#include "sliders.h"
#include "oled.h"
#include "menu.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"


#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz
void main(){

    UART_init(MYUBRR);
    
    SRAM_init();
    oled_reset();
    oled_init();
    menu_init();
    SPI_init();
   
    while(1) {
        //move_cursor();
    	//SPI_write(0xF0);

    }
    
    
    
}
