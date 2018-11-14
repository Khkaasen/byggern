#include "uart.h"
#include <avr/io.h>
#include <stdio.h>


void UART_init(unsigned int ubrr)
{
    /* set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);  // high bits
    UBRR0L = (unsigned char)ubrr;       // low bits

    /* enable reciever and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* set frame format: 8 data bits, 2 stop bits */
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);    

    fdevopen(&UART_Transmit,&UART_Receive); //legg til kommentar her. 
}


void UART_Transmit(unsigned char data)
{
    /* wait for empty transmit buffer */
    while(!(UCSR0A & (1<<UDRE0)));

    /*load data into buffer, send data*/
    UDR0 = data; 
}


unsigned char UART_Receive (void)
{
    /* wait for data to be received */
    while(!(UCSR0A & (1<<RXC0)));

    /* return received data from buffer */
    return UDR0; 
}


