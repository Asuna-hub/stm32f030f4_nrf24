#include "nrf24.h"

//main functions

void NRF24_Init(void){
	SPI1_NRF24_GPIO_Init();
	
	NRF24_CSN_HIGH;
	NRF24_CE_LOW;
	
	SPI1_Init();
	
	//select channel
	NRF24_WriteReg(NRF24_REG_RF_CH, 15);
	
	//select data size
	NRF24_WriteReg(NRF24_REG_RX_PW_P0, 32);
	NRF24_WriteReg(NRF24_REG_RX_PW_P1, 32);
	NRF24_WriteReg(NRF24_REG_RX_PW_P2, 32);
	NRF24_WriteReg(NRF24_REG_RX_PW_P3, 32);
	NRF24_WriteReg(NRF24_REG_RX_PW_P4, 32);
	
	NRF24_SetRF(NRF24_DataRate_2M, NRF24_OutputPower_0dBm);
	
	NRF24_WriteReg(NRF24_REG_CONFIG, NRF24_CONFIG);
	
	//Enable auto-acknowledgment for all pipes
  NRF24_WriteReg(NRF24_REG_EN_AA, 0x3f);
    
  //Enable RX addresses
  NRF24_WriteReg(NRF24_REG_EN_RXADDR, 0x3f);
    
  //Auto retransmit delay: 1000 (4x250) us and Up to 15 retransmit trials
  NRF24_WriteReg(NRF24_REG_SETUP_RETR, 0x4f);

  //Dynamic length configurations: No dynamic length
  NRF24_WriteReg(NRF24_REG_DYNPD, 0);
	
  //clear fifo`s
  NRF24_FLUSH_TX();
  NRF24_FLUSH_RX();
    
  //clear interrupts
  NRF24_ClearStatus();

  NRF24_RX_Config();
}

uint8_t NRF24_ReadReg(uint8_t rg){
	
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_R_REGISTER | rg & 0x1F);
	uint8_t result = SPI_transfer_data(NRF24_CMD_NOP);
	NRF24_CSN_HIGH;
	
	return result;
}

void NRF24_WriteReg(uint8_t rg, uint8_t dt){
	NRF24_CSN_LOW;
	
	SPI_transfer_data(NRF24_CMD_W_REGISTER | rg & 0x1F);
	SPI_transfer_data(dt);
	
	NRF24_CSN_HIGH;
}

void NRF24_WriteBit(uint8_t rg, uint8_t bit, BitAction value) {
    uint8_t tmp;
    tmp = NRF24_ReadReg(rg);
    if (value != Bit_RESET) {
        tmp |= 1 << bit;
    } else {
        tmp &= ~(1 << bit);
    }
    NRF24_WriteReg(rg, tmp);
}

void NRF24_WritePayload(uint8_t *data, uint8_t data_size){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_W_TX_PAYLOAD);
	for (int i = 0; i < data_size; i++){
		SPI_transfer_data(data[i]);
	}
	NRF24_CSN_HIGH;
}

void NRF24_WriteRegm(uint8_t reg, uint8_t *data, uint8_t len){
  NRF24_CSN_LOW;
  SPI_transfer_data(NRF24_CMD_W_REGISTER | reg & 0x1F);
	for (int i = 0; i < len; i++){
		SPI_transfer_data(data[i]);
	}
  NRF24_CSN_HIGH; 
}

void NRF24_ClearStatus(void){
	NRF24_WriteBit(NRF24_REG_STATUS, 4, Bit_SET);
	NRF24_WriteBit(NRF24_REG_STATUS, 5, Bit_SET);
	NRF24_WriteBit(NRF24_REG_STATUS, 6, Bit_SET);
}


// FLUSH functions
void NRF24_FLUSH_RX(void){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_FLUSH_RX);
	NRF24_CSN_HIGH;
}
void NRF24_FLUSH_TX(void){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_FLUSH_TX);
	NRF24_CSN_HIGH;
}

void NRF24_RX_Config(void){
	NRF24_FLUSH_RX();
	NRF24_ClearStatus();
	NRF24_CE_HIGH;
	NRF24_WriteReg(NRF24_REG_CONFIG, 1 << NRF24_EN_CRC | 0 << NRF24_CRCO | 1 << NRF24_PWR_UP | 1 << NRF24_PRIM_RX);
	NRF24_CE_LOW;
}
void NRF24_writeTX(uint8_t *data){
	NRF24_CE_HIGH;
	NRF24_ClearStatus();
	NRF24_WriteReg(NRF24_REG_CONFIG, 1 << NRF24_EN_CRC | 0 << NRF24_CRCO | 1 << NRF24_PWR_UP | 0 << NRF24_PRIM_RX);
	NRF24_FLUSH_TX();
	NRF24_WritePayload(data, 32);
	NRF24_CE_LOW;
}
uint8_t NRF24_ReadRX(uint8_t *result, uint8_t result_size){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_R_RX_PAYLOAD);
	while(result_size--){
		*result++ = SPI_transfer_data(NRF24_CMD_NOP);
	}
	NRF24_CSN_HIGH;
	
	return NRF24_ReadReg(NRF24_REG_STATUS);
}

NRF24_STATUS_REGISTER NRF24_ReadStatus(){
	NRF24_STATUS_REGISTER reg;
	NRF24_CSN_LOW;
  reg.all = SPI_transfer_data(NRF24_REG_STATUS);
	NRF24_CSN_HIGH;
  return reg; 
}

void NRF24_SetRF(NRF24_DataRate_t dr, NRF24_OutputPower_t pow){
    uint8_t tmp = 0;
    if (dr == NRF24_DataRate_2M)
    {
        tmp |= 1 << NRF24_RF_DR_HIGH;
    } else if (dr == NRF24_DataRate_250k) {
		tmp |= 1 << NRF24_RF_DR_LOW;
	}
	//If 1Mbps, all bits set to 0
    
  	if (pow == NRF24_OutputPower_0dBm) {
		tmp |= 3 << NRF24_RF_PWR;
	} else if (pow == NRF24_OutputPower_M6dBm) {
		tmp |= 2 << NRF24_RF_PWR;
	} else if (pow == NRF24_OutputPower_M12dBm) {
		tmp |= 1 << NRF24_RF_PWR;
	}

    NRF24_WriteReg(NRF24_REG_RF_SETUP, tmp);
}

//address
void NRF24_Set_my_addr(uint8_t *addr){
    NRF24_CE_HIGH;
    NRF24_WriteRegm(NRF24_REG_RX_ADDR_P1,addr,5);
    NRF24_CE_LOW;
}

void NRF24_Set_tx_addr(uint8_t *addr){
    NRF24_WriteRegm(NRF24_REG_RX_ADDR_P0,addr,5);
    NRF24_WriteRegm(NRF24_REG_TX_ADDR,addr,5);
}

void NRF24_SelectChannel(uint8_t ch)
{
    NRF24_WriteReg(NRF24_REG_RF_CH, ch);
}

uint8_t NRF24_IsAlive(void) {
    uint8_t setup = NRF24_ReadReg(NRF24_REG_SETUP_AW);
    return (setup == 0x03 || setup == 0x02);
}