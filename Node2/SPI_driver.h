
#ifndef SPI_COM_H_
#define SPI_COM_H_

void SPI_init();

void SPI_write(char cData);

char SPI_read();

void spi_slave_select(int state);


#endif