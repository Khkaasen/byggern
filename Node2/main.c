#define F_CPU 16000000  //16MHz
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
//#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "PWM_driver.h"
#include "joystick_driver.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz

//ACM0 putty
void main(){


  	UART_init(MYUBRR);
    SPI_init();
    //printf("%d",MCP_read_status());
   	CAN_init();
    PWM_init();
    /*
  	uint8_t b[2] = {0xFF,0x1d};
   	can_message msg = 
   	{
   		.length=2,
   		.id=1,
   		.RTR=0
   	};
    msg.data[0] = b[0];

    */

    can_message msg;



  	//printf("start program \n");
    //printf("data1 after read: %x \n", msg.data[1]);
    //printf("data2 after read: %x \n", msg.data[1]);
    //printf("length after read (2): %x \n",msg.length);
    //printf("id after read (5): %x \n",msg.id);
	

    while(1) {

     //PWM_set_duty_cycle(-100);

      msg=CAN_receive();

      //printf("X  : %d \n", msg.data[0]);
      //printf("Y  : %d \n", msg.data[1]);
      //printf("DIR: %d \n", msg.data[2]);
      joystick_to_servopos(msg);
      //_delay_ms(500);
            //printf("%x\n", MCP_read(MCP_CANINTF));

  	}
    
    
    
}
