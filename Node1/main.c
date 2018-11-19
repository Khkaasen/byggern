#define F_CPU 4915200UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"

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
#include "game.h"
#include "fsm.h"

#include <avr/interrupt.h>

#include "EEPROM_driver.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//Cutoff frequency: 796.18 Hz
//ttyS0 putty


void init_all()
{

  	cli();

    UART_init(MYUBRR);
    printf("all init done\n");
    SRAM_init();
    oled_reset();
    multi_card_init();
    oled_init(); //denne skjer nå i multi_card_init();                // what is this comment
    menu_init();

    //printf("%d",MCP_read_status());
    CAN_init();

    fsm_init();

    sei();
}


void main(){    

  
  init_all();

  //printf("all init done\n");

  fsm();

  /*

   	printf("program start\n");

    int8_t b[2] = {100,-100};
   	 can_message msg = 
   	{
   		.length=2,
   		.id=5,
   		.RTR=0
   	};
    msg.data[0] = b[0];
    msg.data[1]=b[1];
     _delay_ms(10);
*/
/*
    CAN_transmit(msg);
*/
   
    
    //joystick_status joy = get_joystick_status();
    /*
    printf("Joystick X:%d\n", joy.x);
    printf("Joystick Y:%d\n", joy.y);
    printf("Joystick dir:%d\n", joy.dir);

    transmit_joystick_status(joy);
    */
    
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
    /*EEPROM_write(11,250);

    //printf("%d\n", msg.data);
   	//CLEAR_BIT(PORTB,PB4);

    joystick_struct joy;

     sliders_struct slider;

     buttons_struct buttons;

    while(1) {
      printf("in main\r\n" );
      joy = get_joystick_status();
      
      slider = get_sliders_status();

      buttons = get_buttons_status();

      transmit_IO_card(slider, joy, buttons);

      if(msg_rec.id == 3 )
      {
        break;
      }
      /* Hvorfor delay? */
     //_delay_ms(10);
        
}
