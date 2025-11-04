#include "main.h"

#include <stdio.h>

NRF24_STATUS_REGISTER status_reg;
uint8_t str[32] = "Hello loxi by nRF24\n";
uint8_t data[32] = {0};
uint8_t result[32];


void TX(void){
	NRF24_TX_mode();
	NRF24_CONFIG_REGISTER conf = NRF24_ReadConfig();
	delay_s(5);
	NRF24_SendTX(str);
	//delay_s(10);
	//NRF24_STATUS_REGISTER stat = NRF24_ReadStatus();
	while(!(nrf_irq_flag));
	NRF24_STATUS_REGISTER stat = NRF24_ReadStatus();
}
void RX(void){
	NRF24_RX_mode();
	NRF24_CONFIG_REGISTER conf = NRF24_ReadConfig();
	uint8_t stat_rx = NRF24_ReadReg(NRF24_REG_STATUS);
	while(!(nrf_irq_flag));
	stat_rx = NRF24_ReadReg(NRF24_REG_STATUS);
	//stat_rx = NRF24_ReadRX(result, 32);
}
int main(void){
	RCC_Init();
	SysTick_Init();
	nrf_irq_init();
	TIM3_Init();
	NRF24l01_init();
	NRF24_EN_AA_REGISTER en_aaa = NRF24_Read_EN_AA();
	uint8_t p0 = NRF24_ReadReg(NRF24_REG_RX_ADDR_P0);
	uint8_t tx = NRF24_ReadReg(NRF24_REG_TX_ADDR);
	NRF24_FIFO_STATUS_REGISTER fifo = NRF24_Read_FIFO_STATUS();
	NRF24_OBSERVE_TX_REGISTER obs = NRF24_Read_OBSERVE_TX();
	//TX();
	RX();
	while(1);
}