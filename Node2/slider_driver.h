#ifndef slider_driver_h
#define slider_driver_h


#include <stdint.h>
#include "CAN_driver.h"

#define SLIDER_LEFT 0
#define SLIDER_RIGHT 1
#define SLIDER_ID 2


void position_controller_init();
int32_t slider_to_motorref(can_message msg);

void position_controller(int32_t ref);

int16_t live_calibration();

#endif //slider_driver.h