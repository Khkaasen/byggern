#ifndef sliders_h
#define sliders_h

#include <stdint.h>

typedef struct sliders_status
{
    uint8_t left_slider;
    uint8_t right_slider;
    
} sliders_struct ;

sliders_struct get_sliders_status();

void transmit_sliders_status(sliders_struct slider);

#endif