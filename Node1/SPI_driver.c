#include <avr/io.h>

#include "SPI_driver.h"

void SPI_init()
{
	/* Set MOSI and SCK output, all others in B as input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);

	/* Enable SPI and Master. Set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t SPI_read()
{
	/* write dummy byte to data register */  
	SPDR = 0x00;

	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return data register */
	return SPDR;
}

void SPI_write(char cData)
{
	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}