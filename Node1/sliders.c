#include "usbmultifunction.h"
#include "sliders.h"
#include "CAN_driver.h"
#include <stdio.h>
#include <stdint.h>

#define CHANNEL_LS 6  //CHANNEL left slider
#define CHANNEL_RS 7  //CHANNEL right slider

#define SLIDER_ID 2

#define CONVERT_8_BIT_TO_100 0.3922

sliders get_sliders_status(){

    sliders value;

    //converting sliders to percentage
    value.left_slider = read_channel(CHANNEL_LS)*(CONVERT_8_BIT_TO_100);
    value.right_slider = 100- read_channel(CHANNEL_RS)*(CONVERT_8_BIT_TO_100); //changes direction on the slider (max in the middle)

    printf("left_slider: %4d ",value.left_slider);
    printf("right_slider: %4d \n",value.right_slider);

    return value;
}

void transmit_sliders_status(sliders slider)
{
	int8_t b[2] = {slider.left_slider,slider.right_slider};
    can_message msg=
    {
        .length=2,
        .id=SLIDER_ID, //id = 2 is slider_pos
        .RTR=0
    };
    msg.data[0] = b[0];
    msg.data[1] = b[1];


    CAN_transmit(msg);
}