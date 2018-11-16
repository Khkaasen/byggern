#ifndef SPI_driver_h
#define SPI_driver_h

#include <stdint.h>
#define SET_BIT(reg, bit) (reg |= (1 << bit))      //flytte til mcp til felles?!??
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit))   //flytte til mcp

void SPI_init();
char SPI_read();
void SPI_write(char cData);

#endif