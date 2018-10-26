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
#include "CAN_driver.h"
#include "MCP2515.h"

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
    //printf("%d",MCP_read_status());
   	CAN_init();
   	uint8_t a= 0b11110000;
   	 can_message msg = 
   	{
   		.length=1,
   		.data=&a,
   		.id=5,
   		.RTR=0
   	};

    _delay_ms(10);
    

    /*
    if((MCP_read(MCP_CANSTAT) & MODE_MASK) == MODE_LOOPBACK) //må huske å maske
    {
         printf("hello");

    }
  */ 

 
    printf("length = 1: ");
    printf("%d\n",msg.length);

   	CAN_write(msg);
    printf("length_write = 1: ");
    printf("%d\n",msg.length);

   	msg.length=2;
   	msg.data=0;
    printf("length = 2: ");
   	printf("%d\n",msg.length);

    _delay_ms(1000);
   	msg = CAN_read();
    printf("length_read = 1: ");
    printf("%d\n", msg.length);

    printf("data: ");
    printf("%x\n",msg.data);
   	

    //printf("%d\n", msg.data);
   	//CLEAR_BIT(PORTB,PB4);
    while(1) {
        //move_cursor();
    	//SPI_write(0xF0);

      MCP_read(0x03);
    _delay_ms(1);

    }
    
    
    
}
