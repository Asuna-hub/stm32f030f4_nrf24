#include "nrf24.h"

uint8_t rx_txAddr[] = {0x78, 0x78, 0x78, 0x78, 0x78};

//main functions
void NRF24l01_init(void){
	SPI1_Init();
	delay_uS(5);
	
	SPI1_NRF24_GPIO_Init();
	delay_uS(5);
	
	NRF24_CSN_HIGH;
	NRF24_CE_LOW;
	
	NRF24_WriteReg(NRF24_REG_EN_AA, 1 << NRF24_ENAA_P0); // enable pipe0 aa
	NRF24_WriteReg(NRF24_REG_EN_RXADDR, 1 << NRF24_ERX_P0);
	NRF24_WriteReg(NRF24_REG_RX_PW_P0, 32);
	NRF24_WriteReg(NRF24_REG_SETUP_AW, NRF24_SETUP_AW_5bytes);
	NRF24_WriteReg(NRF24_REG_SETUP_RETR, NRF24_SETUP_RETR_ARD_250uS | NRF24_SETUP_RETR_ARC_15);
	NRF24_WriteReg(NRF24_REG_FEATURE, 0);
	NRF24_WriteReg(NRF24_REG_DYNPD, 0);
	NRF24_ClearStatus();
	NRF24_WriteReg(NRF24_REG_RF_CH, 76);
	NRF24_WriteReg(NRF24_REG_RF_SETUP, NRF24_DataRate_1M | NRF24_OutputPower_M18dBm); //TX_PWR:0dBm, Datarate:1Mbps
}

void NRF24_TX_mode(void){
	NRF24_Set_tx_addr(rx_txAddr);
	NRF24_WriteReg(NRF24_REG_CONFIG, 1 << NRF24_PWR_UP | 0 << NRF24_PRIM_RX | 1 << NRF24_EN_CRC | 1 << NRF24_MASK_MAX_RT);
	NRF24_FLUSH_TX();
	NRF24_FLUSH_RX();
}
void NRF24_RX_mode(void){
	NRF24_Set_rx_addr(rx_txAddr, NRF24_REG_RX_ADDR_P0);
	NRF24_WriteReg(NRF24_REG_CONFIG, 1 << NRF24_PWR_UP | 1 << NRF24_PRIM_RX | 1 << NRF24_EN_CRC);
	NRF24_FLUSH_RX();
	NRF24_FLUSH_TX();
	NRF24_CE_HIGH;
}
void NRF24_SendTX(uint8_t *data){
	NRF24_WritePayload(data, 32);
	NRF24_CE_HIGH;
	delay_uS(150);
	NRF24_CE_LOW;
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
	uint8_t write = NRF24_CMD_W_REGISTER | (rg & 0x1F);
	SPI_transfer_data(write);
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
	delay_uS(5);
}

void NRF24_WriteRegMultiple(uint8_t reg, uint8_t *data, uint8_t len){
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

//address
void NRF24_Set_rx_addr(uint8_t *addr, uint8_t num_pipe){
    NRF24_WriteRegMultiple(num_pipe,addr,5);
}

void NRF24_Set_tx_addr(uint8_t *addr){
    NRF24_WriteRegMultiple(NRF24_REG_RX_ADDR_P0,addr,5);
    NRF24_WriteRegMultiple(NRF24_REG_TX_ADDR,addr,5);
}

//Read functions
NRF24_STATUS_REGISTER NRF24_ReadStatus(){
	NRF24_STATUS_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_STATUS);
	NRF24_CSN_HIGH;
	return reg; 
}
NRF24_CONFIG_REGISTER NRF24_ReadConfig(){
	NRF24_CONFIG_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_CONFIG);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_EN_AA_REGISTER NRF24_Read_EN_AA(){
	NRF24_EN_AA_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_EN_AA);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_EN_RXADDR_REGISTER NRF24_Read_EN_RXADDR(){
	NRF24_EN_RXADDR_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_EN_RXADDR);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_SETUP_AW_REGISTER NRF24_Read_Setup_AW(){
	NRF24_SETUP_AW_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_SETUP_AW);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_SETUP_RETR_REGISTER NRF24_Read_Setup_RETR(){
	NRF24_SETUP_RETR_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_SETUP_RETR);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_RF_CH_REGISTER NRF24_Read_RF_CH(){
	NRF24_RF_CH_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_RF_CH);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_RF_SETUP_REGISTER NRF24_Read_RF_SETUP(){
	NRF24_RF_SETUP_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_RF_SETUP);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_OBSERVE_TX_REGISTER NRF24_Read_OBSERVE_TX(){
	NRF24_OBSERVE_TX_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_OBSERVE_TX);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_RPD_REGISTER NRF24_Read_RPD(){
	NRF24_RPD_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_RPD);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_FIFO_STATUS_REGISTER NRF24_Read_FIFO_STATUS(){
	NRF24_FIFO_STATUS_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_FIFO_STATUS);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_DYNPD_REGISTER NRF24_Read_DYNPD(){
	NRF24_DYNPD_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_DYNPD);
	NRF24_CSN_HIGH;
	return reg;
}
NRF24_FEATURE_REGISTER NRF24_Read_FEATURE(){
	NRF24_FEATURE_REGISTER reg;
	NRF24_CSN_LOW;
	reg.all = NRF24_ReadReg(NRF24_REG_FEATURE);
	NRF24_CSN_HIGH;
	return reg;
}

uint8_t NRF24_ReadRX(uint8_t *data, uint8_t data_size){
	NRF24_CSN_LOW;
	SPI_transfer_data(NRF24_CMD_R_RX_PAYLOAD);
	while(data_size--){
		*data++ = SPI_transfer_data(NRF24_CMD_NOP);
	}
	NRF24_CSN_HIGH;

	return NRF24_ReadReg(NRF24_REG_STATUS);
}