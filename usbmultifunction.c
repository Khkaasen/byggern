#define F_CPU 4915200

#include <util/delay.h>

unsigned char read_channel(int channel)
{
	volatile char* adc = (char *) 0x1400;
	adc[channel] = channel;
	_delay_ms(50);
	return *adc;
}