#include "main.h"

#include <stdio.h>
#include <string.h>

#define LED_Toggle GPIOA->ODR ^= GPIO_ODR_4;
#define LED_On     GPIOA->BSRR = GPIO_BSRR_BS_4;
#define LED_Off    GPIOA->BRR = GPIO_BSRR_BR_4;

NRF24_STATUS_REGISTER status_reg;

/* My address */
uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE7
};
/* Receiver address */
uint8_t TxAddress[] = {
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E
};

void LED_init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER4_1;
	
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
	
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4_1;
}

int main(void){
	RCC_Init();
	LED_init();
	SysTick_Init();
	NRF24_Init();
	
	NRF24_Set_my_addr(MyAddress);
  NRF24_Set_tx_addr(TxAddress);
	
	uint8_t str[32] = "Hello suka by nRF24\n";
  uint8_t dataIn[32];
  uint16_t req = 0;
	
	uint16_t badTransactions = 0;
  uint16_t successfulTransactions = 0; 
	
 while (1){
	status_reg = NRF24_ReadStatus();
	LED_Toggle;
	NRF24_writeTX(str);
	do {
			status_reg = NRF24_ReadStatus();
	} while (status_reg.bit.MAX_RT == 0 && status_reg.bit.TX_DS == 0);
	
	NRF24_ClearStatus();
	
	NRF24_RX_Config();
	do {
			status_reg = NRF24_ReadStatus();
			req++;
			if (req > 1000)
			{
					req = 0;
					break;
			}
	} while (status_reg.bit.RX_DR == 0);
	
	if (status_reg.bit.RX_DR)
		{

			memset(dataIn, 0, 32);

			NRF24_ReadRX(dataIn, 32);
			
			int ret = memcmp(dataIn, str, 32);
			if (ret == 0)
					successfulTransactions++;
			else
					badTransactions++;
		}        

	status_reg = NRF24_ReadStatus();
	}
}