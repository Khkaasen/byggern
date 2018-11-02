#include "SPI_driver.h"
#include <avr/io.h>


void SPI_init()
{

	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_read()
{
	//lag egen funksjon for å velge hvilken slave det skal skrives til


	SPDR = 0x00;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	/* Return data register */

	//egen funksjon her og

	return SPDR;
}


void SPI_write(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}