#define F_CPU 16000000  //16MHz
#include "Motor_driver.h"
#include <avr/io.h>
#include <util/delay.h>

#define OE PH5
#define RST PH6
#define SEL PH3
#define EN PH4
#define DIR PH1


void motor_init()
{
	//set enable, direction, select?, reset and oe pins  as output. 
	DDRH |= (1<<EN) | (1<<DIR)|(1<<OE)|(1<<RST)|(1<<SEL);
	DDRH |= ;

	//set MJ2 as inputs
	DDRK = 0;

	//enable motor
	PORTH |= (1<<PH4);

	//default direction
	PORTH |= (1<<PH1);

	//Toggle RST to reset encoder
	encoder_reset();
}

void set_motor_dir(uint8_t dir)	//spørre studass om type int eller kanskje uint8_t
{
	//SE PÅ OPP-HØYRE/VENSTRE DIR
	if(dir==0)
		PORTH&= ~(1<<PH1);
	else
		PORTH |=(dir<<PH1);
}


int16_t read_encoder()
{
	int16_t encoder_read;
	//set OE (active low) low to enable output of encoder
	PORTH &= ~(1<<OE);

	//set SEL lov to get high byte and wait 20ms
	PORTH &= ~(1<<SEL);	
	_delay_ms(20); //??

	//read MSB
	encoder_read = PINK<<8;

	//Set SEL high to get low byte and wait 20ms
	PORTH |= (1<<SEL);
	_delay_ms(20);

	//read LSB
	encoder_read+=PINK;

	/*
	//Toggle !RST to reset encoder??
	PORTH &= ~(1<<RST);
	_delay_ms(20);
	PORTH |= (1<<RST);
	*/

	//set !OE high to disable output of encoder
	PORTH |= (1<<OE);

	return encoder_read;

}

void encoder_reset()
{
	//Toggle RST to reset encoder

	PORTH &= ~(1<<RST);
	_delay_ms(20);
	PORTH |= (1<<RST);


}