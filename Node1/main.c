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
    multi_card_init();
    //oled_init(); //denne skjer nå i multi_card_init(); 
    menu_init();
    SPI_init();
    //printf("%d",MCP_read_status());
   	CAN_init();

    printf("program start\n");

/*
    uint8_t b[2] = {0xFF,0x0dc};
   	 can_message msg = 
   	{
   		.length=2,
   		.id=5,
   		.RTR=0
   	};
    msg.data[0] = b[0];
    msg.data[1]=b[1];
     _delay_ms(10);

     

    CAN_transmit(msg);
*/
   
    
    //joystick_status joy = get_joystick_status();
    /*
    printf("Joystick X:%d\n", joy.x);
    printf("Joystick Y:%d\n", joy.y);
    printf("Joystick dir:%d\n", joy.dir);

    transmit_joystick_status(joy);
    */
     _delay_ms(1000);
    
    /*
    if((MCP_read(MCP_CANSTAT) & MODE_MASK) == MODE_LOOPBACK) //må huske å maske
    {
         printf("loopback mode\n");

    }

    */
    //can_message msg_recieve = CAN_read();
    //printf("start program \n");
    //printf("data1 before write: %x \n", msg.data[0]);
    //printf("data2 before write: %x \n", msg.data[1]);

 
    //printf("length before write (1): %x \n",msg.length);
    //printf("id before write (5): %x \n",msg.id);
     
   	
    //printf("length after read (3) %x \n",msg_recieve.length);
    //printf("id after read (1) %x \n",msg_recieve.id);
    //printf("data1 after read: %x \n", msg_recieve.data[0]);
    //printf("data2 after read: %x \n", msg_recieve.data[1]);
    //printf("data3 after read: %x \n", msg.data[2]);
    //printf("length = 2: ");
   	//printf("%d\n",msg.length);
    

    //printf("%d\n", msg.data);
   	//CLEAR_BIT(PORTB,PB4);

     joystick_status joy;

     sliders slider;


    while(1) {

      joy = get_joystick_status();

      slider = get_sliders_status();

      transmit_IO_card(slider, joy);
      //printf("%d\n", slider.right_slider);
      //transmit_joystick_status(joy);

      //_delay_ms(50);

      //transmit_sliders_status(slider);

        //move_cursor();
    	//SPI_write(0xF0);

      //MCP_read(0x03);
      _delay_ms(1);


    }
    
    
    
}
