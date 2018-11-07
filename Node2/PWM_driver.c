#include "PWM_driver.h"
#include <avr/io.h>
#include <stdint.h>


#define F_PWM 50 
#define F_CPU 16000000
#define PRESCALER 8
#define TOP F_CPU/(F_PWM*PRESCALER) -1

#define CENTER_PERCENTAGE 1.5/20
#define GAIN_PERCENTAGE 0.6/20

void PWM_init()
{

	//set "Output Compare Match B" as output 
	DDRB |= (1<<PB6);

	//set operating mode: Fast PWM mode 
	TCCR1A |= (0<<WGM10) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);

	//set Compare Output mode: Non-inverting mode 
	TCCR1A |= (1<<COM1B1) | (0<<COM1B0);

	//set clock source as F_CPU /8 
	TCCR1B |= (0<<CS12) | (1<<CS11) |(0<<CS10); 

	//set TOP value in ICR-register
	ICR1 = TOP;

	//initial position
	PWM_set_duty_cycle(0);


}

void PWM_set_duty_cycle(float percentage)
{

	//printf("%d\n", (int)percentage );
	
	// never set PWM duty cycle outside range
	if((percentage > 100) ||( percentage< -100))
	{
		printf("\npercentage out of range: %d", (int)percentage);
		return;
	}

	//printf("%d\n", (int)percentage );

	float duty_cycle = CENTER_PERCENTAGE + GAIN_PERCENTAGE * percentage/100;
	
	//printf("%d\n",(int)(duty_cycle*100));

	uint16_t compare_flag = duty_cycle * TOP;


	//set compare register to compare value
	OCR1B = compare_flag; 

}


