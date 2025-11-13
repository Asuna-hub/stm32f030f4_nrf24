#ifndef SPI_H
#define SPI_H

#include "main.h"

extern volatile uint8_t nrf_irq_flag;

void SPI1_Init(void);
void SPI1_NRF24_GPIO_Init(void);
uint8_t SPI_transfer_data(uint8_t dt);
void nrf_irq_init(void);
#endif