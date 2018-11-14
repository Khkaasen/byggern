#define F_CPU 4915200
#include "usbmultifunction.h"
#include "oled.h"
#include <stdint.h>
#include <util/delay.h>
#include "oled.h"
#include <avr/io.h>

#define MESSAGE_LENGTH 6

#define IO_ID 1

void multi_card_init()
{
    oled_init();
    DDRB &= ~(1<<PB2); // set this pin as input 
}

unsigned char read_channel(int channel)
{
	volatile char* adc = (char *) 0x1400;
	adc[channel] = channel;                    //hva er syntaks her?
	_delay_ms(50);                             //innterupt istedenfor 
	return *adc;
}

void transmit_IO_card(sliders sliders, joystick_status joystick)
{
	int8_t b[MESSAGE_LENGTH] = {joystick.x,joystick.y,joystick.dir, joystick.button, sliders.left_slider,sliders.right_slider};
    can_message msg=
    {
        .length=MESSAGE_LENGTH,
        .id=IO_ID, //id = 2 is slider_pos
        .RTR=0
    };
    msg.data[0] = b[0];
    msg.data[1] = b[1];
    msg.data[2] = b[2];
    msg.data[3] = b[3];
    msg.data[4] = b[4];
    msg.data[5] = b[5];



    CAN_transmit(msg);
}