#include "main.h"

uint8_t str[32] = "Hello STM32 by nRF24\n";
uint8_t result[32];

uint8_t p0, tx, config, config_dma;
NRF24_STATUS_REGISTER status_reg;
NRF24_FIFO_STATUS_REGISTER fifo;
NRF24_OBSERVE_TX_REGISTER obs;
NRF24_CONFIG_REGISTER conf;
NRF24_STATUS_REGISTER stat;
NRF24_EN_AA_REGISTER en_aa;

uint8_t rx_addr_p0;
uint8_t rx_addr_p1;
uint8_t rx_addr_p2;
uint8_t rx_addr_p3;
uint8_t rx_addr_p4;
uint8_t rx_addr_p5;

NRF24_SETUP_AW_REGISTER setaw;
NRF24_RF_SETUP_REGISTER rfset;

void System_inits(void){
	RCC_Init();
	SysTick_Init();
	DMA_SPI_Init();
	nrf_irq_init();
	TIM3_Init();
}

void TX(void){
	NRF24_TX_mode();
	conf = NRF24_Read_Config();
	delay_s(5);
	NRF24_SendTX(str);
	/*while(!(nrf_irq_flag)){
		NRF24_SendTX(str);
		fifo = NRF24_Read_FIFO_STATUS();
		obs = NRF24_Read_OBSERVE_TX();
	}*/
}
void RX(void){
	NRF24_RX_mode();
	conf = NRF24_Read_Config();
	uint8_t stat_rx = NRF24_ReadReg(NRF24_REG_STATUS);
	fifo = NRF24_Read_FIFO_STATUS();
	while(!(nrf_irq_flag))
	{
		fifo = NRF24_Read_FIFO_STATUS();
		conf = NRF24_Read_Config();
		stat = NRF24_Read_Status();
		delay_s(1);
	}
	stat_rx = NRF24_ReadRX(result, 32);
}
int main(void){
	System_inits();
	NRF24l01_init();
/*	NRF24_Write_Reg_DMA(NRF24_REG_CONFIG, 1 << NRF24_PWR_UP | 0 << NRF24_PRIM_RX | 1 << NRF24_EN_CRC | 1 << NRF24_MASK_MAX_RT);
	config_dma = NRF24_Read_Reg_DMA(NRF24_REG_CONFIG);
	conf = NRF24_Read_Config();
	NRF24_WriteBit_DMA(NRF24_REG_CONFIG, 1, 0);
	config = NRF24_ReadReg(NRF24_REG_CONFIG);*/
//	TX();
//	RX();
	while(1)
	{
		rx_addr_p0 = NRF24_Read_Reg_DMA(NRF24_REG_RX_ADDR_P0);
		tx = NRF24_Read_Reg_DMA(NRF24_REG_TX_ADDR);
		p0 = NRF24_ReadReg(NRF24_REG_RX_ADDR_P0);
		config_dma = NRF24_Read_Reg_DMA(NRF24_REG_STATUS);
//		config = NRF24_ReadReg(NRF24_REG_STATUS);
	}
}