#ifndef MCP2515_driver_h
#define MCP2515_driver_h

#include <stdint.h>

uint8_t MCP_init();
uint8_t MCP_read(uint8_t address);
void MCP_write(int8_t data, uint8_t address);
void MCP_request_to_send();
uint8_t MCP_read_status();
void MCP_bit_modify(uint8_t mask, uint8_t address, int8_t data);
void MCP_reset();
void MCP_read_n_byte(int8_t *data,uint8_t address, uint8_t num_bytes);
void MCP_write_n_byte(int8_t *data, uint8_t address, uint8_t num_bytes);

#endif