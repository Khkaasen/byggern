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
//ttyS0 putty
void main(){


    UART_init(MYUBRR);
    
    SRAM_init();
    oled_reset();
    oled_init();
    menu_init();
    SPI_init();
    //printf("%d",MCP_read_status());
   	CAN_init();
    uint8_t b[2] = {0xFF,0x1d};
   	 can_message msg = 
   	{
   		.length=2,
   		.id=5,
   		.RTR=0
   	};
    msg.data[0] = b[0];
    msg.data[1]=b[1];
    _delay_ms(10);
    

    /*
    if((MCP_read(MCP_CANSTAT) & MODE_MASK) == MODE_LOOPBACK) //må huske å maske
    {
         printf("hello");

    }
  */ 
    //printf("start program \n");
    //printf("data1 before write: %x \n", msg.data[0]);
    //printf("data2 before write: %x \n", msg.data[1]);

 
    //printf("length before write (1): %x \n",msg.length);
    //printf("id before write (5): %x \n",msg.id);

   	
    CAN_write(msg);
    //printf("length after write (1) %x \n",msg.length);
    //printf("id after write (5) %x \n",msg.id);
    //printf("length = 2: ");
   	//printf("%d\n",msg.length);

    //printf("%d\n", msg.data);
   	//CLEAR_BIT(PORTB,PB4);
    while(1) {
        //move_cursor();
    	//SPI_write(0xF0);

      MCP_read(0x03);
    _delay_ms(1);


    }
    
    
    
}
