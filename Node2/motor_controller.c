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
#define GAME_MODE 0
uint16_t encoder_endpoint;
int32_t error_integral;
int32_t last_error;

void controller_select(int8_t game_mode)
{
	//printf("MODE: %d\n",game_mode );

	switch (game_mode){

	/* PID controller */
	case (2): 
		KP= 200;
		KI= 1;
		KD= 50;
		break;

	/* PD controller */
	case (3):
		KP= 300;
		KI= 0;
		KD= 100;
		break;

	/* P controller */
	case (4):
		KP= 300;
		KI= 0;
		KD= 0;
		break;

	/* mirrored P controller */
	case (5):
		KP= 1;
		KI= 0;
		KD= 0; 
		break; 
	}

}

void controller_init()
{
	//uint16_t encoder_read;
	//DAC_set_output(0);
	//encoder_reset();
	//encoder_read = read_encoder();
	//printf("encoder reset:%d\n", encoder_read );

	
	error_integral = 0;
	last_error = 0;
	set_motor_dir(1);

	DAC_set_output(MOTOR_INIT_FORCE);

    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);
    encoder_reset();


    set_motor_dir(0);
    DAC_set_output(MOTOR_INIT_FORCE);
    _delay_ms(2800);
    DAC_set_output(0);
    _delay_ms(500);


    encoder_endpoint = read_encoder();
}

int32_t controller_read_motor_ref(can_message * msg)
{
	int32_t motorref;
	int32_t a = msg->data[SLIDER_RIGHT]; //changes direction on slider

	long b = a*encoder_endpoint;
	//printf("%d\n", read_encoder());
	motorref = b/100;
	//printf("%d\n\r", a);
	//printf("%ld\n\r",b); 
	//printf("%d\n\r",motorref );
	return(motorref);
}


void controller_set_motor_input(can_message * msg)
{	
	//reset encoder hvis den når FFFF

	int32_t ref = controller_read_motor_ref(msg);
	//printf("SLIDER_RIGHT  :%d\n\r", msg->data[SLIDER_RIGHT] );
	int32_t error = ref - read_encoder();
	error_integral +=error;
	int32_t error_derivate = error - last_error;
	int32_t u = error*KP/10000 + error_integral*KI/10000 +error_derivate*KD/10000;
	//printf("ERROR: %d\r\n", error );
	//printf("ref: %d\r\n", ref );
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