#define F_CPU 16000000  //16MHz
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdint.h>
#include "uart.h"
//#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515.h"
#include "MCP_driver.h"
#include "PWM_driver.h"
#include "joystick_driver.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include "TWI_Master.h"
#include "DAC_driver.h"
#include <avr/interrupt.h>
#include "Motor_driver.h"
#include "motor_controller.h"
#include "game.h"
#include "timer.h"
#include "fsm.h"
#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz

  can_message msg_send = {
    .data = {1,5},
    .length=2,
    .id=3,
    .RTR=0
  };
  
  /* dette er lagt inn i fsm
  can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
  };

ISR(INT4_vect) {
  //_delay_ms(100);
  //printf("Hallaais\n\r" );
  //printf("%x\n\r", MCP_read(MCP_CANINTF));

  CAN_receive(&msg_rec);


}
*/

void init_all(){

      cli();
    UART_init(MYUBRR);

    

    //printf("%d",MCP_read_status());

    CAN_init(); // this also inits mcp and spi
    PWM_init();
    ADC_init();
    IR_init();
    TWI_Master_Initialise();
    DAC_init();
    //timer_init();
    motor_init();
    joystick_init();
    

    sei();

}
//ACM0 putty 
void main(){
  
  init_all();
  
    _delay_ms(100);
    //fsm();
    controller_init();
    /*
    while(1)
    {
      if (detect_blockage()){
        printf("sent msg node 2\n");
        CAN_transmit(&msg_send);
      }
    }

    */
}

