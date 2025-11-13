#include "main.h"

uint8_t str[32] = "Hello STM32 by nRF24\n";
uint8_t result[32];

uint8_t p0, tx;
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
	nrf_irq_init();
	TIM3_Init();
}

void TX(void){
	NRF24_TX_mode();
	conf = NRF24_ReadConfig();
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
	conf = NRF24_ReadConfig();
	uint8_t stat_rx = NRF24_ReadReg(NRF24_REG_STATUS);
	fifo = NRF24_Read_FIFO_STATUS();
	while(!(nrf_irq_flag))
	{
		fifo = NRF24_Read_FIFO_STATUS();
		conf = NRF24_ReadConfig();
		stat = NRF24_ReadStatus();
		delay_s(1);
	}
	stat_rx = NRF24_ReadRX(result, 32);
}
int main(void){
	System_inits();
	NRF24l01_init();
	en_aa = NRF24_Read_EN_AA();
	p0 = NRF24_ReadReg(NRF24_REG_RX_ADDR_P0);
	NRF24_WriteReg(NRF24_REG_CONFIG, 0 << NRF24_PWR_UP | 1 << NRF24_PRIM_RX | 1 << NRF24_EN_CRC);
	conf = NRF24_ReadConfig();
	NRF24_WriteBit(NRF24_REG_CONFIG, NRF24_PWR_UP, Bit_SET);
	conf = NRF24_ReadConfig();
	tx = NRF24_ReadReg(NRF24_REG_TX_ADDR);
	fifo = NRF24_Read_FIFO_STATUS();
	obs = NRF24_Read_OBSERVE_TX();
	setaw = NRF24_Read_Setup_AW();
	rfset = NRF24_Read_RF_SETUP();
//	TX();
	RX();
	while(1)
	{
		fifo = NRF24_Read_FIFO_STATUS();
		obs = NRF24_Read_OBSERVE_TX();
		conf = NRF24_ReadConfig();
		stat = NRF24_ReadStatus();
		delay_s(1);
	}
}