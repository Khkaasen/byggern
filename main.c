#define F_CPU 4915200UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include "../joystick.h"
#include "../buttons.h"
#include "../sliders.h"
#include "oled.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz
void main(){

    UART_init(MYUBRR);
    
    SRAM_init();
    //oled_init(); 

    //unsigned char data;
    //while (1){
        //printf("Skriv det du vil at skal sendes:");
        //data=getchar();
    //}
    //printf("heeeeei\n");
	joystick_status joystick;

    //SRAM_test();
    //DDRC = 0xFF; // setter c register til output  
    DDRB = 0x00;
    while(1) {
    	get_joystick_status(); 
        get_sliders_status();
    	//PORTC = 0xFF;
        //oled_print(3);
       	//PORTB = 0xFF;
        //UART_Transmit(UART_Receive());
        //UART_Transmit('b');
        //UART_Transmit('\n');
        //PORTC |= (1 << PC0); // setter dette bitet 1, lar alle andre være
        //PORTC &= ~(1<< PC0); //setter dette bitet 0, lar alle andre være 
        //PORTC = 0x80; 
        //_delay_ms(1000);
        //PORTC = 0x00;
        //PORTA = 0xF5;
        //_delay_ms(1000);
        //printf("a\n");
        //_delay_ms(100);
    }
}
