#define F_CPU 16000000  //16MHz
#include "motor_controller.h"
#include "DAC_driver.h"
#include "Motor_driver.h"
#include "PWM_driver.h"
#include <util/delay.h>

static int32_t KP; 
static int32_t KI;
static int32_t KD;

#define MOTOR_INIT_FORCE 90
#define INTERRUPT_PERIOD 0.0326568

uint16_t encoder_endpoint;
int32_t error_integral;
int32_t last_error;
int32_t error_derivate;

void controller_select(int8_t game_mode)
{

}

void controller_init()
{
	//uint16_t encoder_read;
	//DAC_set_output(0);
	//encoder_reset();
	//encoder_read = read_encoder();
	//printf("encoder reset:%d\n", encoder_read );

	//enable overflow interrupt enable
	TIMSK1 | = (1<<TOIE1);

	//set timer2 to normal mode
	TCCR0A &= ~(1<<WGM10);
	TCCR0A &= ~(1<<WGM11);
	TCCR0B &= ~(1<<WGM12);
	TCCR0B &= ~(1<<WGM13);

	//set prescale to 8
	TCCR0B &= ~(1<<CS10);
	TCCR0B |= (1<<CS11);
	TCCR0B &= ~(1<<CS12);


	error_integral = 0;
	last_error = 0;
	set_motor_dir(1);
	DAC_set_output(MOTOR_INIT_FORCE);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);
    encoder_reset();
    //encoder_read = read_encoder();
    //printf("Initial start pos:%d\n", encoder_read );

    //_delay_ms(1000);
    
    //encoder_endpoint = read_encoder();
    //printf("%d\n",encoder_endpoint );


    set_motor_dir(0);
    DAC_set_output(MOTOR_INIT_FORCE);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);


    encoder_endpoint = read_encoder();
    set_max_point(encoder_endpoint);
    //printf("Endpoint %d\n", encoder_endpoint);
    //_delay_ms(1000);
}

int32_t controller_read_motor_ref(can_message msg)
{
	int32_t motorref;
	if(msg.id==IO_ID)
	{
		int32_t a = msg.data[SLIDER_RIGHT]; //changes direction on slider
		long b = a*encoder_endpoint;
		//printf("%d\n", read_encoder());
		motorref = b/100;
		//printf("%d\n", a);
		//printf("%ld\n",b); 
		//printf("%d\n",motorpos );
		//_delay_ms(1000);
		return(motorref);
	}
}

ISR(TIMER1_OFV_vec)
{
	int32_t ref = controller_read_motor_ref(msg);
	int32_t error = ref - read_encoder();
	error_integral +=error*INTERRUPT_PERIOD;
	error_derivate = (error - last_error)/INTERRUPT_PERIOD;
	int32_t u = error*KP/10000 + error_integral*KI/10000 +error_derivate*KD/10000;

	input_saturation(u);
	input_direction(u);


	DAC_set_output(abs(u));

	last_error = error;
}

void input_saturation(int16_t u)
{
	if(abs(u)>255)
	{
		u=255;
	}
}

void input_direction(int8_t u)
{
	if (u<0)
		set_motor_dir(1);
	else
		set_motor_dir(0);
}



//finn på noe smart !!!
int16_t live_calibration()
{
	/*
	uint16_t motorpos = read_encoder();
	if(motorpos>encoder_endpoint)
	{
		DAC_set_output(0);
		motorpos = encoder_endpoint;
	}
	else if(motorpos<0)
	{
		DAC_set_output(0);
		motorpos = 0;
	}
	else
		motorpos=read_encoder();
	return motorpos;
	*/
}