#include "usbmultifunction.h"
#include "sliders.h"
#include <stdio.h>
#include <stdint.h>

#define CHANNEL_LS 6  //CHANNEL left slider
#define CHANNEL_RS 7  //CHANNEL right slider

#define CONVERT_8_BIT_TO_100 0.3922

sliders get_sliders_status(){

    sliders value;

    //converting sliders to percentage
    value.left_slider = read_channel(CHANNEL_LS)*(CONVERT_8_BIT_TO_100);
    value.right_slider = read_channel(CHANNEL_RS)*(CONVERT_8_BIT_TO_100);

    printf("left_slider: %4d ",value.left_slider);
    printf("right_slider: %4d \n",value.right_slider);

    return value;
}