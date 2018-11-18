#ifndef EEPROM_driver_h
#define EEPROM_driver_h 
#include <stdint.h>

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_read(unsigned int uiAddress);

unsigned char EEPROM_test(unsigned int uiAddress, unsigned char ucData);

#endif
