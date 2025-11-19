#include "main.h"

uint8_t str[32] = "Hello STM32 by nRF24\n";
uint8_t result[32];

uint8_t p0, tx, config, config_dma, rx_pw_p0;
NRF24_STATUS_REGISTER status_reg;
NRF24_FIFO_STATUS_REGISTER fifo;
NRF24_OBSERVE_TX_REGISTER obs;
NRF24_CONFIG_REGISTER conf;
NRF24_STATUS_REGISTER stat;
NRF24_EN_AA_REGISTER en_aa;
NRF24_EN_RXADDR_REGISTER en_rxaddr;
NRF24_SETUP_AW_REGISTER setup_aw;
NRF24_SETUP_RETR_REGISTER setup_retr;
NRF24_FEATURE_REGISTER feat;
NRF24_DYNPD_REGISTER dyn;
NRF24_RF_CH_REGISTER rf_ch;
NRF24_RF_SETUP_REGISTER rf_setup;

uint8_t rx_addr_p0;
uint8_t rx_addr_p1;
uint8_t rx_addr_p2;
uint8_t rx_addr_p3;
uint8_t rx_addr_p4;
uint8_t rx_addr_p5;

void System_inits(void){
	RCC_Init();
	SysTick_Init();
	DMA_SPI_Init();
	nrf_irq_init();
	TIM3_Init();
}

void TX(void){
	NRF24_TX_mode_DMA();
	conf = NRF24_Read_Config();
	config_dma = NRF24_Read_Reg(NRF24_REG_CONFIG);
	rx_addr_p0 = NRF24_Read_Reg(NRF24_REG_RX_ADDR_P0);
	p0 = NRF24_Read_Reg_DMA(NRF24_REG_RX_ADDR_P0);
	delay_s(5);
	NRF24_SendTX_DMA(str, 32);
/*	while(!(nrf_irq_flag)){
		NRF24_SendTX(str);
		fifo = NRF24_Read_FIFO_STATUS();
		obs = NRF24_Read_OBSERVE_TX();
	}*/
}
void RX(void){
	NRF24_RX_mode_DMA();
	conf = NRF24_Read_Config();
	uint8_t stat_rx = NRF24_Read_Reg_DMA(NRF24_REG_STATUS);
	fifo = NRF24_Read_FIFO_STATUS();
	while(!(nrf_irq_flag))
	{
		fifo = NRF24_Read_FIFO_STATUS();
		conf = NRF24_Read_Config();
		stat = NRF24_Read_Status();
		delay_s(1);
	}
	stat_rx = NRF24_Read_RX_DMA(result, 32);
}
int main(void){
	System_inits();
	NRF24L01_DMA_Init();
	en_aa = NRF24_Read_EN_AA();
	en_rxaddr = NRF24_Read_EN_RXADDR();
	rx_pw_p0 = NRF24_Read_Reg(NRF24_REG_RX_PW_P0);
	setup_aw = NRF24_Read_Setup_AW();
	setup_retr = NRF24_Read_Setup_RETR();
	feat = NRF24_Read_FEATURE();
	dyn = NRF24_Read_DYNPD();
	rf_ch = NRF24_Read_RF_CH();
	rf_setup = NRF24_Read_RF_SETUP();
//	TX();
	RX();
	while(1);
}