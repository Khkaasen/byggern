
#include <avr/io.h>

#include "SPI_driver.h"

void SPI_init() {
	/* Set MOSI, SCK and SS output, all others input */
	DDRB = (1<<PB1)|(1<<PB2)|(1<<PB7)|(1<<PB0);

	/* Enable SPI, Master, set clock rate fck/16 */	/*kan sette bit 7 idette registeret for interrupt enable*/
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

	PORTB |= (1<<PB0);
}

void SPI_write(char cData) {

	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

char SPI_read() {

	SPDR = 0x00;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF))) {
	}

	/* Return data register */
	return SPDR;
}

void spi_slave_select(int state){
	if (state) {
		PORTB &= ~(1 << PB7);
		} else {
		PORTB |= (1 << PB7);
	}
}