#ifndef SPI_H
#define SPI_H

#include "main.h"

void SPI1_Init(void);
void SPI1_NRF24_GPIO_Init(void);
uint8_t SPI_transfer_data(uint8_t dt);

#endif