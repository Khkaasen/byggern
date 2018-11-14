#ifndef usbmultifunction_h
#define usbmultifunction_h

#include "joystick.h"
#include "sliders.h"
#include "CAN_driver.h"

unsigned char read_channel(int channel);
void transmit_IO_card(sliders sliders, joystick_status joystick);

#endif