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
#include "fsm.h"
#include "EEPROM_driver.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//Cutoff frequency: 796.18 Hz
//ttyS0 putty

void init_all()
{
  	cli();

    UART_init(MYUBRR);
    SRAM_init();
    oled_reset();
    multi_card_init();
    menu_init();
    CAN_init();
    fsm_init();

    sei();
}

void main()
{    
  init_all();

  fsm();
}