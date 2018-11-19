#ifndef MCP2515_driver_h
#define MCP2515_driver_h

#include <stdbool.h>
#include <stdint.h>

void MCP_init();

void MCP_bit_modify(char address, char mask,   char data);

void MCP_reset();

char MCP_read(char address);

void MCP_write(int8_t data, uint8_t address);

void MCP_request_to_send();

uint8_t MCP_read_status();

void MCP_read_n_bytes(char address,int8_t * data, char length);

void MCP_write_n_bytes(char address,int8_t * data, char length);

#endif