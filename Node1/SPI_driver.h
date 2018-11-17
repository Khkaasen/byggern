#ifndef SPI_driver_h
#define SPI_driver_h

#include <stdint.h>

#define SET_BIT(reg, bit) (reg |= (1 << bit))  //skal vi bruke disse overalt? marius synes ikke disse er nødvenig så lenge vi bare bruker de her. 
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit)) // samme gjelder denne. 

void SPI_init();

uint8_t SPI_read();

void SPI_write(char cData);

#endif