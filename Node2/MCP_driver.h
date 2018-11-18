/*
 * MCP_com.h
 *
 * Created: 19.10.2018 17:16:43
 *  Author: margronv
 */ 


#ifndef MCP_COM_H_
#define MCP_COM_H_


// MCP
void MCP_init();

void MCP_bit_modify(char address, char mask,   char data);

void MCP_reset();

char MCP_read(char address);

void MCP_write(int8_t data, uint8_t address);

void MCP_request_to_send();

uint8_t MCP_read_status();


#endif /* MCP_COM_H_ */