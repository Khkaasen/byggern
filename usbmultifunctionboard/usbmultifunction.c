#define F_CPU 4915200
#include "usbmultifunction.h"
#include <stdint.h>
#include <util/delay.h>

unsigned char read_channel(int channel)
{
	volatile char* adc = (char *) 0x1400;
	adc[channel] = channel;                    //hva er syntaks her?
	_delay_ms(50);                             //innterupt istedenfor 
	return *adc;
}