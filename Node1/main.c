#define F_CPU 4915200UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

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
#include "EEPROM_driver.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

/* Cutoff frequency: 796.18 Hz */
/* ttyS0 putty */


/* Initialiserer can_message */
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

/* Interrupt */
ISR(INT0_vect)
{

  CAN_receive(&msg_rec);
}

void main()
{    
  cli();

    UART_init(MYUBRR);
    SRAM_init();
    oled_reset();
    multi_card_init();
    oled_init(); //denne skjer nå i multi_card_init();                // what is this comment
    menu_init();

/* mcp_init() og spi_init skjer i can_init */
   	CAN_init();

    sei();

   	printf("program start\n");

    joystick_struct joy;

     sliders_struct slider;

     buttons_struct buttons;

    while(1) 
    {
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
     _delay_ms(10);
    }    
}
