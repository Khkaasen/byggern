##ifndef EEPROM_driver_h
#define EEPROM_driver_h 
#include <stdint.h>

void EEPROM_write(uint8_t data);

unsigned char EEPROM_read(unsigned int uiAddress);

#endif
