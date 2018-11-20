#include "ADC_driver.h"
#include <avr/io.h>


void ADC_init()
{
	
	DDRF |= (0<<PF0);

	//Set ADC 0 as single input
	ADMUX |= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	ADCSRB |= (0<<MUX5);

	//Set AREF as voltage reference
	ADMUX |=(0<<REFS1)|(0<<REFS0);

	//Enable ADC
	ADCSRA |= (1<<ADEN);

	//Prescale CPU with division factor 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
}

uint16_t ADC_read()
{
	uint16_t data;
	//Start Conversion
	ADCSRA |= (1<<ADSC);
	
	//wait for conversion to complete
	while((ADCSRA & (1<<ADSC)));

	data = ADC;

	return data;
}
