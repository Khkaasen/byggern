#include "IR_driver.h"
#include "ADC_driver.h"

#include <util/delay.h>

static int blockage;

#define IR_HIGH 195  //voltage 
#define LOWER_BOUND 0.25 
#define HIGHER_BOUND 0.75

void IR_init()
{
	blockage= 0;

}



uint8_t detect_blockage()
{


	uint16_t IR_signal = ADC_read();


	if (blockage==0 && IR_signal< (IR_HIGH*LOWER_BOUND)) 
	{
		blockage = 1;
		return 1; 
	}

	if(blockage == 1 && IR_signal> (IR_HIGH*HIGHER_BOUND))
	{
		blockage=0;  
	}
	return 0;
}
