#ifndef NRF24_N_H
#define NRF24_N_H

//CSN
#define NRF24_CSN_HIGH GPIOA->BSRR = GPIO_BSRR_BS_4
#define NRF24_CSN_LOW  GPIOA->BSRR = GPIO_BSRR_BR_4
//CE
#define NRF24_CE_HIGH  GPIOB->BSRR = GPIO_BSRR_BS_1
#define NRF24_CE_LOW   GPIOB->BSRR = GPIO_BSRR_BR_1

//Configuration bits
#define NRF24_MASK_RX_DR		6
#define NRF24_MASK_TX_DS		5
#define NRF24_MASK_MAX_RT	  4
#define NRF24_EN_CRC			  3
#define NRF24_CRCO			    2
#define NRF24_PWR_UP			  1
#define NRF24_PRIM_RX		    0

#define NRF24_PLL_LOCK		  4
#define NRF24_RF_DR_LOW		  5
#define NRF24_RF_DR_HIGH	  3
#define NRF24_RF_DR			    3
#define NRF24_RF_PWR        1 //2 bits 



#endif