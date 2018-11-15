#define F_CPU 16000000  //16MHz
#include "slider_driver.h"
#include "DAC_driver.h"
#include "Motor_driver.h"
#include "PWM_driver.h"
#include <util/delay.h>

#define KP 150 
#define KI 1
#define KD 20

uint16_t encoder_endpoint;
int32_t error_integral;
int32_t last_error;

void position_controller_init()
{
	uint16_t encoder_read;
	//DAC_set_output(0);
	encoder_reset();
	//encoder_read = read_encoder();
	//printf("encoder reset:%d\n", encoder_read );
	error_integral = 0;
	last_error = 0;
	set_motor_dir(1);
	DAC_set_output(100);
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
    DAC_set_output(100);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);


    encoder_endpoint = read_encoder();
    //printf("Endpoint %d\n", encoder_endpoint);
    //_delay_ms(1000);
}

int32_t slider_to_motorref(can_message msg)
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


void position_controller(int32_t ref)
{	
	//reset encoder hvis den når FFFF

	int32_t error = ref - read_encoder();
	error_integral +=error;
	int32_t error_derivate = error - last_error;
	//printf("ref:%ld\n", ref);
	//printf("error:%ld\n", error);
	int32_t u = error*KP/10000 + error_integral*KI/10000 +error_derivate*KD/10000;
	if(abs(u)>255)
	{
		u=255;
	}
	//printf("u:%ld\n", u);
	if (u<0)
	{
		set_motor_dir(1);
	}
	else
	{
		set_motor_dir(0);
	}

	DAC_set_output(abs(u));

	last_error = error;
}



//finn på noe smart !!!
int16_t live_calibration()
{
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
}