#include "SPI_driver.h"
#include <avr/io.h>


void SPI_init()
{

	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB5)|(1<<DDB7)|(1<<PB4);

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_read()
{
	//lag egen funksjon for å velge hvilken slave det skal skrives til
	CLEAR_BIT(PORTB, PB4);


	SPI_write(0x00);
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	/* Return data register */

	//egen funksjon her og
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


