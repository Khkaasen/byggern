/*
 * spi_com.h
 *
 * Created: 01.11.2018 09:00:08
 *  Author: margronv
 */ 


#ifndef SPI_COM_H_
#define SPI_COM_H_

void SPI_init();
void SPI_write(char cData);
char SPI_read();
void spi_slave_select(int state);


#endif /* SPI_COM_H_ */