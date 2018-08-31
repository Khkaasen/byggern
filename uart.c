#include "uart.h"
#include <avr/io.h>


void UART_init(unsigned int ubrr){

    UBRR0H = (unsigned char)(ubrr>>8);    //set baud rate
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);    //enable reciever and transmitter

    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);    //Set frame format: 8data, 2 stop bit
}

void UART_Transmit(unsigned char data){
    while(!(UCSR0A & (1<<UDRE0)))     //wait for empty transmit
        ;

    //printf("Sent!!");
    UDR0 = data; //Put data into buffer, sends the data

}
unsigned char USART_Receive (void){
    //Wait for data to be received

    while(!(UCSR0A & (1<<RXC0)))
        ;
    //Get and return received data from buffer
    return UDR0; 
}

void UART_Flush(void){
    unsigned char dummy;
    //while ( UCSRA & (1<<RXC)) dummy = UDR;
}


