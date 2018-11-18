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
#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz

  can_message msg_send = {
    .data = {5,5},
    .length=2,
    .id=0,
    .RTR=0
  };
  
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


//ACM0 putty 
void main(){
  
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
    _delay_ms(100);
    printf("BITCH START\n");

    //controller_init();
    

  
    //uint8_t blockage;

//    int16_t encoder;
    
//printf ("%x\r\n",MCP_read(MCP_CANINTF));

    //msg = CAN_receive();

    //printf ("%x\r\n",MCP_read(MCP_CANINTF));
  	//printf("start program \n");
    //printf("data1 after read: %d ", msg.data[1]);
    //printf("data2 after read: %x \n", msg.data[1]);
    //printf("length after read : %d ",msg.length);
    //printf("id after read : %d \n\r",msg.id);

    //timer_test();
    //printf("right before main loop\n");
    while(1) {
      
      //printf("data1 after read: %d ", msg.data[1]);
      //printf("data2 after read: %x \n", msg.data[1]);
      //printf("length after read : %d ",msg.length);
      //printf("id after read : %d \n\r",msg.id);

      //printf("r in main loop\n\r");
      //printf("data: %d ",msg_send.data[0]);
      //printf("data: %d \n\r ",msg_send.id);
      //data = ADC_read();


      //count_goals();
      //printf("%d\n", get_n_goals());

      //printf("%d\n", data);

     //PWM_set_duty_cycle(-100);

      //CAN_receive();
      //printf("main while 1 \n");

      //game_start(msg);
      if (detect_blockage()){
        //cli(); vetke om dette trengs egt.
        CAN_transmit(&msg_send);
        printf("node 2 has sent can message\n");
        //sei();
      }
      

      //printf ("%x\r\n",MCP_read(MCP_CANINTF));
       // printf("%x\n\r", MCP_read(MCP_EFLG));

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
      //printf("Data: %d  ", msg.data[0] );
      //printf("ID: %d\n\r", msg.id);
      //printf("%d\n", data );

      //set_motor_dir(dir);
      //printf("Right B  : %d \n", msg.data[6]);
      //printf("Left B  : %d \n", msg.data[7]);
      //printf("DIR: %d \n", msg.data[2]);
      //joystick_to_servopos(msg);
      //_delay_ms(10);
            //printf("%x\n", MCP_read(MCP_CANINTF));

  	}
    
    
}

