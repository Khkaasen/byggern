#include "usbmultifunction.h"
#include "sliders.h"
#include "CAN_driver.h"
#include <stdio.h>
#include <stdint.h>

#define CHANNEL_LS 6  //CHANNEL left slider
#define CHANNEL_RS 7  //CHANNEL right slider
#define SLIDER_ID 2
#define CONVERT_GAIN 0.3922

sliders_struct get_sliders_status()
{

    sliders_struct value;

    /*converting sliders to percentage with absolute value */
    value.left_slider = read_channel(CHANNEL_LS)*(CONVERT_GAIN);
    value.right_slider = 100- read_channel(CHANNEL_RS)*(CONVERT_GAIN); 

    return value;
}

void transmit_sliders_status(sliders_struct slider)
{
    /* initalize can message with correct data bytes*/
	int8_t b[2] = 
    {
        slider.left_slider,
        slider.right_slider
    };

    can_message msg=
    {
        .length=2,
        .id=SLIDER_ID, //id = 2 is slider_pos
        .RTR=0
    };

    msg.data[0] = b[0];
    msg.data[1] = b[1];

    /* transmit can message to can */
    CAN_transmit(&msg);
}


