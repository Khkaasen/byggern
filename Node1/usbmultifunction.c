#define F_CPU 4915200

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "usbmultifunction.h"
#include "oled.h"

#define MESSAGE_LENGTH 8

#define IO_ID 1
#define ADC_MEMORYMAP 0x1400

void multi_card_init()
{
    oled_init();

    /* set PB2 as output*/
    DDRB &= ~(1<<PB2); 
}

unsigned char read_channel(int channel)
{
	volatile char* adc = (char *) ADC_MEMORYMAP;
	adc[channel] = channel;
	_delay_ms(50);
	return *adc;
}

void transmit_IO_card(sliders_struct sliders, joystick_struct joystick, buttons_struct buttons)
{
	/* initialize can message with correct data bytes */
	int8_t byte[MESSAGE_LENGTH] = 
	{	
		joystick.x,
		joystick.y,
		joystick.dir, 
		joystick.button, 
		sliders.left_slider,
		sliders.right_slider,
        buttons.right,
        buttons.left
	};
    
    can_message msg=
    {
        .length=MESSAGE_LENGTH,
        .id=IO_ID,
        .RTR=0
    };

    msg.data[0] = byte[0];
    msg.data[1] = byte[1];
    msg.data[2] = byte[2];
    msg.data[3] = byte[3];
    msg.data[4] = byte[4];
    msg.data[5] = byte[5];
    msg.data[6] = byte[6];
    msg.data[7] = byte[7];

    /* transmit can message to can */
    CAN_transmit(&msg);

}