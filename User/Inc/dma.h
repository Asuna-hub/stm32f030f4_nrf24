#ifndef DMA_H
#define DMA_H

#include "main.h"

void DMA_SPI_Init(void);
void SPI_DMA_Transmit(uint8_t data, uint16_t size);
void SPI_DMA_Receive(uint8_t buffer, uint16_t size);

#endif