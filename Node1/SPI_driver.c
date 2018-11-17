#include "SPI_driver.h"
#include <avr/io.h>


void SPI_init()
{
	//her gjør vi ting litt annerledes enn aksel. sjekk opp.

	/* set MOSI and SCK output, all others in B as input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);

	/* enable SPI and Master. set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


uint8_t SPI_read()
{
	

	/* write dummy byte to data register */  
	SPDR = 0x00; 	// denne linjen kan byttes ut med SPI_write(0). 

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