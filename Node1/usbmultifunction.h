#ifndef usbmultifunction_h
#define usbmultifunction_h

#include "joystick.h"
#include "sliders.h"
#include "CAN_driver.h"
#include "buttons.h"


void multi_card_init();

unsigned char read_channel(int channel);

void transmit_IO_card(sliders_struct sliders, joystick_struct joystick, buttons_struct buttons);

#endif