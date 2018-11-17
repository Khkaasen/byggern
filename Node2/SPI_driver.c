#include "SPI_driver.h"
#include <avr/io.h>


//chip select signal, PB7, IKKE PB0. Resten er PB1 osv...

void SPI_init()
{

	/* Set MOSI, SCK and SS output, all others input */
	DDRB = (1<<PB1)|(1<<PB2)|(1<<PB7)|(1<<PB0);

	/* Enable SPI, Master, set clock rate fck/16 */				/*kan sette bit 7 idette registeret for interrupt enable*/
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_read()
{
	//lag egen funksjon for å velge hvilken slave det skal skrives til


	SPDR = 0x00;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF))) {
	}
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