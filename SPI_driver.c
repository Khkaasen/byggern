#include "SPI_driver.h"
#include <avr/io.h>

#define SET_BIT(reg, bit) (reg |= (1 << bit))
#define CLEAR_BIT(reg, bit) (reg &= ~(1 << bit))

void SPI_init()
{

	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB5)|(1<<DDB7)|(1<<PB4);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_read()
{
	CLEAR_BIT(PORTB, PB4);


	SPI_write(0x00);
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	/* Return data register */

	SET_BIT(PORTB, PB4);

	return SPDR;
}


void SPI_write(char cData)
{
	CLEAR_BIT(PORTB, PB4);
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	SET_BIT(PORTB, PB4);
}


