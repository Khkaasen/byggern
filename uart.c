#include "uart.h"


void UART_init(unsigned int ubrr){

    UBRRH = (unsigned char)(ubrr>>8);    //set baud rate
    UBRRL = (unsigned char)ubrr;

    UCSRB = (1<<RXEN)|(1<<TXEN);    //enable reciever and transmitter

    UCRSC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);    //Set frame format: 8data, 2 stop bit
}


void UART_Transmit(unsigned char data){
    while(!(UCSRA & (1<<UDRE)))     //wait for empty transmit
        ;

    printf("Sent!!");
    UDR = data; //Put data into buffer, sends the data

}
unsigned char USART_Receive (void){
    //Wait for data to be received

    while(!(UCSRA & (1<<RXC)))
        ;
    //Get and return received data from buffer
    return UDR; 
}

void UART_Flush(void){
    unsigned char dummy;
    while ( UCSRA & (1<<RXC)) dummy = UDR;
}


