#define F_CPU 4915200UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "sram.h"
#include "joystick.h"
#include "buttons.h"
#include "sliders.h"
#include "oled.h"
#include "menu.h"

#define Baudrate 9600
#define MYUBRR F_CPU/16/Baudrate-1

//testprogram med jtag
//Cutoff frequency: 796.18 Hz
void main(){

    UART_init(MYUBRR);
    
    SRAM_init();
    oled_reset();
    oled_init();
    menu_init();
    //int len = sizeof(menulist)/sizeof(menulist[0]);
    //printf("%d\n",len );
    //printf(menulist[3]);
    //oled_print(menulist[0]);
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
    //????????????????????????????????????????????????????????????????????????????? PS vi lurer på hvorfor vi må ta inn streng og ikke char hehe :PPP   XDDDD LOOOOLLLL lurer også på fdv setup shit
    //oled_print("hei");
    //oled_print_char('w');

    while(1) {
        move_cursor();
    	
    	//printf("a");
        //print_test();

    	//get_joystick_status(); 
        //get_sliders_status();
    	//PORTC = 0xFF;
        //oled_print(3);
       	//PORTB = 0xFF;
        //UART_Transmit(UART_Receive());
        //UART_Transmit('b');
        //UART_Transmit('\n');
        //oled_init();

        //PORTC |= (1 << PC0); // setter dette bitet 1, lar alle andre være
        //PORTC &= ~(1<< PC0); //setter dette bitet 0, lar alle andre være 
        //PORTC = 0x80; 
        //_delay_ms(1000);
        //PORTC = 0x00;
        //PORTA = 0xF5;
        //_delay_ms(1000);
        //printf("a\n");
    }
    
    
    
}
