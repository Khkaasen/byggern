#ifndef sliders_h
#define sliders_h

#include <stdint.h>

typedef struct sliders_status
{
    uint8_t left_slider;
    uint8_t right_slider;
    
} sliders ;

sliders get_sliders_status();

void transmit_sliders_status(sliders slider);

#endif