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
#include "MCP2515_driver.h"
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
#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz

//ACM0 putty
void main(){
    cli();

  	UART_init(MYUBRR);
    SPI_init();
    //printf("%d",MCP_read_status());
   	CAN_init();
    PWM_init();
    ADC_init();
    IR_init();
    TWI_Master_Initialise();
    DAC_init();
    //timer_init();
    motor_init();
    joystick_init();

    //printf("BITCH START\n");
    sei();
    _delay_ms(100);
    
    //controller_init();
    
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
    uint8_t blockage;
    can_message msg;

    int16_t encoder;

  	//printf("start program \n");
    //printf("data1 after read: %x \n", msg.data[1]);
    //printf("data2 after read: %x \n", msg.data[1]);
    //printf("length after read (2): %x \n",msg.length);
    //printf("id after read (5): %x \n",msg.id);

    //timer_test();
    //printf("right before main loop\n");
    while(1) {


      printf("r in main loop\n");

      //data = ADC_read();


      //count_goals();
      //printf("%d\n", get_n_goals());

      //printf("%d\n", data);

     //PWM_set_duty_cycle(-100);

      msg=CAN_receive();
      //printf("main while 1 \n");

      //game_start(msg);



      //printf("main while 2\n");



      //ref =slider_to_motorref(msg);
      //position_controller(ref);
     //encoder=live_calibration();
      //encoder = read_encoder();
      //printf("%d\n", encoder);
      //joystick_to_servopos(msg);
      //joystick_button_to_soleniode(msg);

      //data =joystick_to_motorspeed(msg);
      //uint8_t dir = joystick_to_motordir(msg);
      printf("%d\n", msg.data[1] );
      printf("%d\n", msg.id);
      //printf("%d\n", data );

      //set_motor_dir(dir);
      //printf("Right B  : %d \n", msg.data[6]);
      //printf("Left B  : %d \n", msg.data[7]);
      //printf("DIR: %d \n", msg.data[2]);
      //joystick_to_servopos(msg);
      //_delay_ms(500);
            //printf("%x\n", MCP_read(MCP_CANINTF));

  	}
    
    
    
}
