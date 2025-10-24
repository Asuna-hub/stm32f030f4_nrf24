#ifndef SPI_H
#define SPI_H

#include "main.h"

#define NSS_SET GPIOA->BSRR = GPIO_BSRR_BS_4
#define NSS_RESET GPIOA->BSRR = GPIO_BSRR_BR_4

void SPI1_Init(void);
void SPI1_NRF24_GPIO_Init(void);
#endif