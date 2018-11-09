#include "DAC_driver.h"
#include "TWI_Master.h"

//First four bits of the slave address 0101 0000
#define DAC_address 0x50;


//DAC commandbits
#define RST 5
#define PD 4

//Digital address byte
#define A0 1

static uint8_t DAC_message[3];
	

	

void DAC_init()
{
	DAC_message[0] = DAC_address;
	DAC_message[1] = (1<<RST);

	TWI_Start_Transceiver_With_Data(DAC_message,3);
}


void DAC_set_output(uint8_t output) //må finne nytt navn
{

	//Command/output byte
	DAC_message[1] = (0<<RST)|(0<<PD)|(A0<<0);
	
	//data byte
	DAC_message[2]=output;

	//send message
	TWI_Start_Transceiver_With_Data(DAC_message, 3);

}
