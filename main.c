#include "main.h"

#include <stdio.h>
#include <string.h>

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
void Module1_Transmitter(void) {
    NRF24_Init();
    
    NRF24_Set_tx_addr(MyAddress);
    NRF24_Set_my_addr(TxAddress); 
    
    uint8_t counter = 0;
    uint8_t tx_data[32] = {0};
    
    while(1) {
        for(int i = 0; i < 32; i++) {
            tx_data[i] = counter + i;
        }
        
        // ??????????
        printf("TX: Sending packet %d\r\n", counter);
        NRF24_writeTX(tx_data);

        uint8_t status = NRF24_ReadReg(NRF24_REG_STATUS);
        printf("Status: 0x%02X\r\n", status);
        
        if(status & (1 << 5)) {
            printf("TX: Success!\r\n");
        }
        if(status & (1 << 4)) { 
            printf("TX: Max retries reached!\r\n");
        }
        
        NRF24_ClearStatus();
        counter++;
        delay_mS(1000);
    }
}

void Module2_Receiver(void) {
    NRF24_Init();
    
    NRF24_Set_my_addr(MyAddress);
    NRF24_Set_tx_addr(TxAddress);
    
    NRF24_RX_Config();
    
    uint8_t rx_data[32] = {0};
    uint8_t packet_count = 0;
    
    printf("RX: Ready to receive...\r\n");
    
    while(1) {
        if(!(NRF24_ReadReg(NRF24_REG_FIFO_STATUS) & 0x01)) {
            uint8_t status = NRF24_ReadRX(rx_data, 32);
            
            printf("RX: Received packet %d! Status: 0x%02X\r\n", 
                   packet_count, status);
            
            printf("Data: ");
            for(int i = 0; i < 5; i++) {
                printf("%02X ", rx_data[i]);
            }
            printf("\r\n");
            
            packet_count++;
            
            NRF24_ClearStatus();
        }
        
        delay_mS(100);
    }
}

int main(void){

}