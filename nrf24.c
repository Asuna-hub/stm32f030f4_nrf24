#include "nrf24.h"

//main functions
uint8_t NRF24_read_reg(uint8_t rg){
	
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_R_REGISTER | rg & 0x1F);
	uint8_t result = SPI_transfer_data(NRF24_CMD_NOP);
	NRF24_CSN_HIGH;
	
	return result;
}

void NRF24_write_reg(uint8_t rg, uint8_t dt){
	NRF24_CSN_LOW;
	
	SPI_transfer_data(NRF24_CMD_W_REGISTER | rg & 0x1F);
	SPI_transfer_data(dt);
	
	NRF24_CSN_HIGH;
}

void NRF24_WriteBit(uint8_t rg, uint8_t bit, BitAction value) {
    uint8_t tmp;
    tmp = NRF24_read_reg(rg);
    if (value != Bit_RESET) {
        tmp |= 1 << bit;
    } else {
        tmp &= ~(1 << bit);
    }
    NRF24_write_reg(rg, tmp);
}

void NRF24_WritePayload(uint8_t *data, uint8_t data_size){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_W_TX_PAYLOAD);
	for (int i = 0; i < data_size; i++){
		SPI_transfer_data(*data+i);
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
	SPI_transfer_data(NRF24_CMD_FLUSH_RX);
	NRF24_CSN_HIGH;
}



void NRF24_RX_mode(void){
	NRF24_FLUSH_RX();
	NRF24_ClearStatus();
	NRF24_CE_HIGH;
	NRF24_write_reg(NRF24_REG_CONFIG, 1 << NRF24_EN_CRC | 0 << NRF24_CRCO | 1 << NRF24_PWR_UP | 1 << NRF24_PRIM_RX);
	NRF24_CE_LOW;
}
void NRF24_writeTX(uint8_t *data){
	NRF24_CE_HIGH;
	NRF24_ClearStatus();
	NRF24_write_reg(NRF24_REG_CONFIG, 1 << NRF24_EN_CRC | 0 << NRF24_CRCO | 1 << NRF24_PWR_UP | 0 << NRF24_PRIM_RX);
	NRF24_FLUSH_TX();
	NRF24_WritePayload(data, 32);
	NRF24_CE_LOW;
}
uint8_t nrf24_readRX(uint8_t *result, uint8_t result_size){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_R_RX_PAYLOAD);
	while(result_size--){
		*result++ = SPI_transfer_data(NRF24_CMD_NOP);
	}
	NRF24_CSN_HIGH;
	
	return NRF24_read_reg(NRF24_REG_STATUS);
}

nRF24L01_STATUS_REGISTER nRF24L01_readStatus(){
	
    nRF24L01_STATUS_REGISTER reg;
    reg.all = SPI_transfer_data(NRF24_REG_STATUS);
    
    return reg; 
}