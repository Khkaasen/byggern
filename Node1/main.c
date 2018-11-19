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

#include <avr/interrupt.h>

#include "EEPROM_driver.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz
//ttyS0 putty

  can_message msg_send = {
    .length=1,
    .id=10,
    .RTR=0
  };
  int8_t b[2] = {100,-100};


  can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
  };

ISR(INT0_vect)
{

  CAN_receive(&msg_rec);
}

void main(){    

  
  cli();

    UART_init(MYUBRR);
    //SPI_init();
    //MCP_init();
    //printf("!!!! \n");
    SRAM_init();
    oled_reset();
    multi_card_init();
    oled_init(); //denne skjer nå i multi_card_init(); 
    menu_init();
    //printf("!!!! \n");

    //printf("%d",MCP_read_status());
   	CAN_init();

    sei();

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
    msg_send.data[0] = b[0];

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
    //EEPROM_write(11,250);

    //printf("%d\n", msg.data);
   	//CLEAR_BIT(PORTB,PB4);

    joystick_struct joy;

     sliders_struct slider;

     buttons_struct buttons;
     /*
     //game();
    //printf("%d\n",test );
    //display_countdown();
    // uint8_t i= 123;
    uint8_t a=123;
    //uint8_t c=EEPROM_read(11);
    uint8_t hei=EEPROM_read(11);
    printf("%d\n",hei);
    oled_display_game_over(a,hei);
 */
    while(1) {

      //printf("in main while loop\n\r");
      //oled_print_pic();
      
      joy = get_joystick_status();
      
      slider = get_sliders_status();

      buttons = get_buttons_status();


      transmit_IO_card(slider, joy, buttons);

      //printf("transmitted IO card\r\n");


      msg_send.data[0] = joy.x;



      //CAN_transmit(&msg_send);

      //printf("joystick X sent: %d\r\n", msg_send.data[0] );
      if(msg_rec.id == 3 )
      {
        break;
      }
      
     //printf("Joystick X received: %d\n\r",msg_rec.data[0]);
      

      //CAN_transmit(msg);
      //msg=CAN_receive();

      //printf("Data: %d  ", msg.data[0] );
      //printf("ID: %d\n\r", msg.id);
      //printf("%d\n", data );
      //oled_display_game_over(i);
      //menu_change_menu();

      //menu_change_menu();
      
      //enu_change_menu();

      //printf("%d\n", slider.right_slider);
      //transmit_joystick_status(joy);

      //_delay_ms(50);

      //transmit_sliders_status(slider);

        //move_cursor();
    	//SPI_write(0xF0);

      //MCP_read(0x03);
     _delay_ms(10);


    }
    
    
    
}
