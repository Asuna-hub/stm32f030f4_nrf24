#ifndef NRF24_H
#define NRF24_H

#include "main.h"

//CSN
#define NRF24_CSN_HIGH GPIOA->BSRR = GPIO_BSRR_BS_4
#define NRF24_CSN_LOW  GPIOA->BSRR = GPIO_BSRR_BR_4
//CE
#define NRF24_CE_HIGH  GPIOB->BSRR = GPIO_BSRR_BS_1;
#define NRF24_CE_LOW   GPIOB->BSRR = GPIO_BSRR_BR_1;

//RF setup register
#define NRF24_PLL_LOCK		  4
#define NRF24_RF_DR_LOW		  5
#define NRF24_RF_DR_HIGH	  3
#define NRF24_RF_DR			  3
#define NRF24_RF_PWR	      1 //2 bits   


typedef enum {
    Bit_RESET = 0,
    Bit_SET = 1
} BitAction;

//Data rate
//--------------------------------------------------------------
typedef enum{
	NRF24_DataRate_1M,	// 2Mbps
	NRF24_DataRate_2M		// 1Mbps
}NRF24_DataRate_t;
//--------------------------------------------------------------


//Config registers
//--------------------------------------------------------------
enum NRF24_ConfigReg{
	NRF24_REG_CONFIG     = 0x00, // don't touch
	NRF24_REG_EN_AA      = 0x01, // Auto Acknowledgment for pipe
	NRF24_REG_EN_RXADDR  = 0x02, // Enable data pipe 0
	NRF24_REG_SETUP_AW   = 0x03, // Setting the address width
	NRF24_REG_SETUP_RETR = 0x04, // Setting up retransmission
	NRF24_REG_RF_CH      = 0x05, // RF channels
	NRF24_REG_RF_SETUP   = 0x06, // Setting RF
	NRF24_REG_STATUS     = 0x07, // Status register
	NRF24_REG_OBSERVE_TX = 0x08, 
	NRF24_REG_RPD        = 0x09
};
//--------------------------------------------------------------


//Address registers 
//--------------------------------------------------------------
enum nRF24_AddressReg{
  NRF24_REG_RX_ADDR_P0 = 0x0A, // receive address data pipe
  NRF24_REG_RX_ADDR_P1 = 0x0B,
  NRF24_REG_RX_ADDR_P2 = 0x0C,
  NRF24_REG_RX_ADDR_P3 = 0x0D,
  NRF24_REG_RX_ADDR_P4 = 0x0E,
  NRF24_REG_RX_ADDR_P5 = 0x0F,
  NRF24_REG_TX_ADDR    = 0x10  //Transmit address
};
//--------------------------------------------------------------


//Packet size registers
//--------------------------------------------------------------
typedef enum {
	NRF24_REG_DYNPD    = 0x1C,
  NRF24_REG_RX_PW_P0 = 0x11, // Number of bytes in RX payload in data pipe 0 (1 to 32 bytes).
  NRF24_REG_RX_PW_P1 = 0x12, // Number of bytes in RX payload in data pipe 1
  NRF24_REG_RX_PW_P2 = 0x13, // Number of bytes in RX payload in data pipe 2
  NRF24_REG_RX_PW_P3 = 0x14, // Number of bytes in RX payload in data pipe 3
  NRF24_REG_RX_PW_P4 = 0x15, // Number of bytes in RX payload in data pipe 4
  NRF24_REG_RX_PW_P5 = 0x16  // Number of bytes in RX payload in data pipe 5
} nRF24_PacketSizeReg_t;
//--------------------------------------------------------------


//Commands
//--------------------------------------------------------------
enum NRF24_Commands{
	NRF24_CMD_R_REGISTER         = 0x00, // read command and status registers
	NRF24_CMD_W_REGISTER         = 0x20, // write command and status registers
	NRF24_CMD_R_RX_PAYLOAD       = 0x61, // read RX-payload
	NRF24_CMD_W_TX_PAYLOAD       = 0xA0, // write TX-payload
	NRF24_CMD_FLUSH_TX           = 0xE1, // Flush TX FIFO, used in TX mode
	NRF24_CMD_FLUSH_RX           = 0xE2, // Flush RX FIFO, used in RX mode
	NRF24_CMD_REUSE_TX_PL        = 0xE3, // Used for a PTX device. Reuse last transmitted payload
	NRF24_CMD_ACTIVATE           = 0x50, // This write command followed by data 0x73 activates the following features:
                                       // • R_RX_PL_WID
                                       // • W_ACK_PAYLOAD
                                       // • W_TX_PAYLOAD_NOACK
	NRF24_CMD_R_RX_PL_WID        = 0x60, // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
	NRF24_CMD_W_ACK_PAYLOAD      = 0xA8, // Used in RX mode. Write Payload to be transmitted together with ACK packet on PIPE PPP
	NRF24_CMD_W_TX_PAYLOAD_NOACK = 0xB0, // Used in TX mode. Disables AUTOACK on this specific packet.
	NRF24_CMD_NOP                = 0xFF  // No Operation. Might be used to read the STATUS register
};
//--------------------------------------------------------------


// CONFIG register bits
//--------------------------------------------------------------
enum NRF24_ConfigBits {
  NRF24_CONFIG_PRIM_RX     = 0x01,  // RX/TX control
  NRF24_CONFIG_PWR_UP      = 0x02,  // Power up
  NRF24_CONFIG_CRCO        = 0x04,  // CRC encoding (0=1 byte, 1=2 bytes)
  NRF24_CONFIG_EN_CRC      = 0x08,  // Enable CRC
  NRF24_CONFIG_MASK_MAX_RT = 0x10,  // Mask MAX_RT interrupt
  NRF24_CONFIG_MASK_TX_DS  = 0x20,  // Mask TX_DS interrupt  
  NRF24_CONFIG_MASK_RX_DR  = 0x40,  // Mask RX_DR interrupt
	NRF24_REG_FEATURE        = 0x1D
};
//--------------------------------------------------------------


// STATUS register bits
//--------------------------------------------------------------
enum NRF24_StatusBits {
  NRF24_STATUS_TX_FULL     = 0x01,  // TX FIFO full flag
  NRF24_STATUS_RX_P_NO     = 0x0E,  // Data pipe number for the payload available for reading from RX_FIFO
                                    // 000-101: Data Pipe Number
                                    // 110: Not Used
                                    // 111: RX FIFO Empty
  NRF24_STATUS_MAX_RT      = 0x10,  // Maximum number of TX retransmits interrupt. Write 1 to clear bit. If MAX_RT is asserted it must be cleared to enable further communication.
  NRF24_STATUS_TX_DS       = 0x20,  // Data Sent TX FIFO interrupt. Asserted when packet transmitted on TX. If AUTO_ACK is activated, this bit is set high only when ACK is received. Write 1 to clear bit.
  NRF24_STATUS_RX_DR       = 0x40   // Data Ready RX FIFO interrupt. Asserted when new data arrives RX FIFO. Write 1 to clear bit.
};

struct nRF24L01_STATUS_REG_BITS {
  uint8_t TX_FULL : 1; // bit 0: TX FIFO is full
  uint8_t RX_P_NO : 3; // bit 1 - 3: number of pipe
  uint8_t MAX_RT  : 1; // bit 4: max. number of retransmissions exceeded
  uint8_t TX_DS   : 1; // bit 5: succesful transmit
  uint8_t RX_DR   : 1; // bit 6: the data are ready to read
  uint8_t res     : 1; // Reserved
};

typedef  union {
    struct nRF24L01_STATUS_REG_BITS bit;
    uint8_t all;
} nRF24L01_STATUS_REGISTER;
//--------------------------------------------------------------


// RF_SETUP register bits
//--------------------------------------------------------------
typedef enum {
  NRF24_RF_SETUP_RF_PWR     = 0x06,  // RF output power mask
  NRF24_RF_SETUP_RF_DR_HIGH = 0x08, // High data rate bit
  NRF24_RF_SETUP_PLL_LOCK   = 0x10,  // PLL lock
  NRF24_RF_SETUP_RF_DR_LOW  = 0x20,  // Low data rate bit  
  NRF24_RF_SETUP_CONT_WAVE  = 0x80   // Continuous carrier transmit
} NRF24_RfSetupBits_t;
//--------------------------------------------------------------


// FIFO_STATUS register bits
//--------------------------------------------------------------
enum NRF24_FifoStatusBits_t{
	NRF24_REG_FIFO_STATUS          = 0x17,
  NRF24_FIFO_STATUS_RX_EMPTY     = 0x01,  // RX FIFO empty
  NRF24_FIFO_STATUS_RX_FULL      = 0x02,  // RX FIFO full
  NRF24_FIFO_STATUS_TX_EMPTY     = 0x10,  // TX FIFO empty
  NRF24_FIFO_STATUS_TX_FIFO_FULL = 0x20,  // TX FIFO full
  NRF24_FIFO_STATUS_TX_REUSE     = 0x40   // TX reuse
};
//--------------------------------------------------------------

//Configuration register
#define NRF24_MASK_RX_DR		6
#define NRF24_MASK_TX_DS		5
#define NRF24_MASK_MAX_RT	  4
#define NRF24_EN_CRC			  3
#define NRF24_CRCO			    2
#define NRF24_PWR_UP			  1
#define NRF24_PRIM_RX		    0

struct NRF24_CONFIG_REG_BITS {
  uint8_t PRIM_RX     : 1; // bit 0: mode (0=TX, 1=RX)
  uint8_t PWR_UP      : 1; // bit 1: power (0=OFF, 1=ON)
	uint8_t CRCO        : 1; // bit 2: CRC lengh (0=1 byte, 1=2 bytes)
  uint8_t EN_CRC      : 1; // bit 3: CRC enable
  uint8_t MASK_MAX_RT : 1; // bit 4: interrupt mask MAX_RT
  uint8_t MASK_TX_DS  : 1; // bit 5: interrupt mask TX_DS
  uint8_t MASK_RX_DR  : 1; // bit 6: interrupt mask RX_DS
  uint8_t res         : 1; // Reserved
};

// Timings
#define NRF24_CE_TIME_mkS			10

#endif
