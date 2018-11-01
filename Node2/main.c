#define F_CPU 16000000  //16MHz
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz
void main(){


  UART_init(MYUBRR);
 
  
  while(1) {

    printf("test");  
  }
    
    
    
}
