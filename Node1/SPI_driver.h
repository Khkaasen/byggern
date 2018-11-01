#include <stdint.h>
#define SET_BIT(reg, bit) (reg |= (1 << bit))
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit))

void SPI_init();
char SPI_read();
void SPI_write(char cData);
