#ifndef DMA_H
#define DMA_H

#include "main.h"

void DMA_SPI_Init(void);
void SPI_DMA_transfer_data(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);
void SPI_DMA_RX_TX_ON(void);
void SPI_DMA_RX_TX_OFF(void);
void DMA_RX_TX_ON(void);
#endif