#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


#define F_CPU 16000000 // do not need this. eventuelt show how i found 156. 

static int8_t extra_timer; 
static int8_t timer;
void timer_init()
{
	
	DDRE |= (1 << PE4); //set flag output as output //mighit not need to set this. i just want to increment a variable. 
	
	TCCR0A = (1 << WGM01); //set CTC mode

	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescaler to 1024

	OCR0A = 156;  // set compare number. flag should be set when number of ticks is 156

	TIMSK0 = (1 << OCIE0A);

	sei();

	extra_timer =0;

	timer = 0; 
}

void timer_start()
{
	timer = 0; 
}

void timer_reset() //ikke sikkert jeg trenger denne. 
{
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

	for (int i=1; i< 100000, i++){
		//this loop waits or time to go
	}

	int8_t newtime = timer_read_time();

	printf("timer after for loop %d\n", newtime);

}

/* increment timer when timer interrupt falg is set 100 times. */
IRS(TIMER0_COMPA_vect) 
{
	extratimer++;

	if(extra_timer==100){
		timer+=1;
		extratimer=0;
	}
}

