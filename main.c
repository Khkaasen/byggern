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
   		.id=1,
   		.RTR=0
   	};
    //printf("start:\n");


    
    if(MCP_read(MCP_CANSTAT) & 01000000)
    {
         printf("hello, m0th3rfuck3r");


    } 

 
    /*
    printf("%d\n",msg.length);

   	CAN_write(msg);
    printf("%d\n",msg.length);

   	msg.length=2;
   	msg.data=0;
   	printf("%d\n",msg.length);

    _delay_ms(1000);
   	msg = CAN_read();
  
   	
    printf("%d\n", msg.length);
   	*/
    //printf("%d", msg.data);
   	
    while(1) {
        //move_cursor();
    	//SPI_write(0xF0);

    }
    
    
    
}
