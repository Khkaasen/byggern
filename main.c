#define F_CPU 4915200UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag

void main(){

    UART_init(MYUBRR);

    unsigned char data;
    while (1){
        //printf("Skriv det du vil at skal sendes:");
        //data=getchar();
        UART_Transmit('a');
    }


    /*
    DDRC = 0xFF; // setter c register til output  
    DDRA = 0xFF;

    while(1) {
        PORTC = 0xFF;
        PORTA = 0xFF;
        //PORTC |= (1 << PC0); // setter dette bitet 1, lar alle andre være
        //PORTC &= ~(1<< PC0); //setter dette bitet 0, lar alle andre være 
        //PORTC = 0x80; 
        _delay_ms(2000);
        PORTC = 0x00;
        PORTA = 0X00;
        _delay_ms(2000);
    }
    */

}