#ifndef uart_h
#define uart_h 

void UART_init(unsigned int ubrr);

void UART_Transmit(unsigned char data);

unsigned char UART_Receive (void);

#endif
