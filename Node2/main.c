#define F_CPU 16000000  //16MHz
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515.h"
#include "MCP_driver.h"
#include "PWM_driver.h"
#include "joystick_driver.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include "TWI_Master.h"
#include "DAC_driver.h"

#include "Motor_driver.h"
#include "motor_controller.h"
#include "timer.h"
#include "fsm.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//Cutoff frequency: 796.18 Hz

void init_all(){

    cli();

    UART_init(MYUBRR);
    CAN_init(); 
    TWI_Master_Initialise();
    PWM_init();
    ADC_init();
    IR_init();
    DAC_init();
    motor_init();
    joystick_init();

    sei();

}



void main(){
  
  init_all();
   
  _delay_ms(100);

  fsm();

}
