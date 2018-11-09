#include <stdint.h>

void motor_init();
void set_motor_dir(uint8_t dir);
uint16_t read_encoder();