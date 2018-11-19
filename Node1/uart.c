#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

void UART_init(unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable reciever and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8 data bits, 2 stop bits */
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);    

    /* Configure function printf */
    fdevopen(&UART_Transmit,&UART_Receive);
}

void UART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while(!(UCSR0A & (1<<UDRE0)));

    /* Load data into buffer, send data */
    UDR0 = data; 
}

unsigned char UART_Receive (void)
{
    /* Wait for data to be received */
    while(!(UCSR0A & (1<<RXC0)));

    /* Return received data from buffer */
    return UDR0; 
}


