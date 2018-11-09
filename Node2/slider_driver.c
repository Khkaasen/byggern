#define F_CPU 16000000  //16MHz
#include "slider_driver.h"
#include "DAC_driver.h"
#include "Motor_driver.h"
#include "PWM_driver.h"
#include <util/delay.h>

#define KP 150

uint16_t encoder_endpoint;

void position_controller_init()
{


	DAC_set_output(50);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);
    encoder_reset();

    //_delay_ms(1000);
    
    //encoder_endpoint = read_encoder();
    //printf("%d\n",encoder_endpoint );


    set_motor_dir(0);
    DAC_set_output(50);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);

    encoder_endpoint = read_encoder();
    printf("Endpoint %d\n", encoder_endpoint);
    //_delay_ms(1000);
}

int32_t slider_to_motorref(can_message msg)
{
	int32_t motorref;
	if(msg.id==SLIDER_ID)
	{
		int32_t a = msg.data[SLIDER_RIGHT]; //changes direction on slider
		long b = a*encoder_endpoint;
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
	int32_t error = ref - read_encoder();
	//printf("ref:%ld\n", ref);
	//printf("error:%ld\n", error);
	int32_t u = error*KP/10000;
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