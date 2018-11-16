#ifndef Motor_driver_h
#define Motor_driver_h

#include <stdint.h>

void motor_init();
void set_motor_dir(uint8_t dir);
int16_t read_encoder();
void encoder_reset();

#endif