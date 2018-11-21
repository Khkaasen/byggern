#include "timer.h"
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>



static int8_t extra_timer; 
static int8_t timer;
void timer_init()
{


	DDRB |= (1 << PB4); //set flag output as output //mighit not need to set this. i just want to increment a variable. 
	
	TCCR0A |= (1 << WGM01); //set CTC mode

	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescaler to 1024

	OCR0A = 20000;  // set compare number. flag should be set when number of ticks is 156

	extra_timer =0;

	timer = 0; 
}

void timer_start()
{
	TCNT0  = 0;//set counter register to 0

	timer = 0; 
}

void timer_reset() //ikke sikkert jeg trenger denne. 
{
	TCNT0  = 0;//set counter register to 0

	timer = 0; 


}

int8_t timer_read_time()
{
	return timer; 
}



void timer_test(){

	timer_init();

	timer_start();

	printf("timer right after start %d\n", timer);

	_delay_ms(3000);

	int8_t newtime = timer_read_time();

	printf("timer after for loop %d\n", newtime);

}

/* increment timer when timer interrupt falg is set 100 times. */
ISR(PCINT7_vect) 
{
	extra_timer++;

	if(extra_timer==100){
		
		timer+=1;
		extra_timer=0;
	}
}

