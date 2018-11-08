#include "DAC_driver.h"

//First four bits of the slave address 0101 0000
volatile char* DAC_address = (char*) 0x50;

//DAC commandbits
#define RST 5
#define PD 4

//Digital address byte
#define A0 1

void DAC_init()
{

}


void DAC_set_output(uint8_t output) //må finne nytt navn
{
	//START, pull SDA low???


	//Slave address bit
	

	//Command byte
	DAC_address[1] = (1<<RST)|(0<<PD)|(1<<A0);

}
