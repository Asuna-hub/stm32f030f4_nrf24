#ifndef DMA_H
#define DMA_H

#include "main.h"

#define DMA_CH2_ON DMA1_Channel2->CCR |= DMA_CCR_EN
#define DMA_CH3_ON DMA1_Channel3->CCR |= DMA_CCR_EN

#define SPI_DMA_RX_ON SPI1->CR2 |= SPI_CR2_RXDMAEN
#define SPI_DMA_RX_OFF SPI1->CR2 &= ~SPI_CR2_RXDMAEN
#define SPI_DMA_TX_ON SPI1->CR2 |= SPI_CR2_TXDMAEN
#define SPI_DMA_TX_OFF SPI1->CR2 &= ~SPI_CR2_TXDMAEN

void DMA_SPI_Init(void);
void SPI_DMA_transfer_data(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);
void SPI_DMA_RX(uint8_t *rx_data, uint16_t size);
void SPI_DMA_TX(uint8_t *tx_data, uint16_t size);
void SPI_DMA_RX_TX_ON(void);
void SPI_DMA_RX_TX_OFF(void);
#endif