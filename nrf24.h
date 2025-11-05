#ifndef NRF24_H
#define NRF24_H

#include "main.h"

/* My address */ 


//CSN
#define NRF24_CSN_HIGH GPIOA->BSRR = GPIO_BSRR_BS_4
#define NRF24_CSN_LOW  GPIOA->BSRR = GPIO_BSRR_BR_4
//CE
#define NRF24_CE_HIGH  GPIOB->BSRR = GPIO_BSRR_BS_1
#define NRF24_CE_LOW   GPIOB->BSRR = GPIO_BSRR_BR_1
 
#define NRF24_CONFIG	 ((1 << NRF24_EN_CRC) | (0 << NRF24_CRCO))

//Configuration bits
#define NRF24_MASK_RX_DR     6
#define NRF24_MASK_TX_DS     5
#define NRF24_MASK_MAX_RT	 4
#define NRF24_EN_CRC         3
#define NRF24_CRCO			 2
#define NRF24_PWR_UP         1
#define NRF24_PRIM_RX        0

//RF_Setup
#define NRF24_PLL_LOCK        4
#define NRF24_RF_DR_LOW       5
#define NRF24_RF_DR_HIGH      3
#define NRF24_RF_PWR          1 //2 bits 

//Enable autoacknowledge
#define NRF24_ENAA_P0       0
#define NRF24_ENAA_P1       1
#define NRF24_ENAA_P2       2
#define NRF24_ENAA_P3       3
#define NRF24_ENAA_P4       4
#define NRF24_ENAA_P5       5

//EX_RXADDR bits
#define NRF24_ERX_P5	  5
#define NRF24_ERX_P4	  4
#define NRF24_ERX_P3	  3
#define NRF24_ERX_P2      2
#define NRF24_ERX_P1	  1
#define NRF24_ERX_P0	  0

//SETUP_AW bits
#define NRF24_SETUP_AW_3bytes (1 << 0)
#define NRF24_SETUP_AW_4bytes (1 << 1) 
#define NRF24_SETUP_AW_5bytes (1 << 0) | (1 << 1)

//SETUP_RETR
#define NRF24_ARD_POS 4
#define NRF24_ARD_MASK (0xF << NRF24_ARD_POS)

#define NRF24_SETUP_RETR_ARD_250uS   (0x0 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_500uS   (0x1 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_750uS   (0x2 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_1000uS  (0x3 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_1250uS  (0x4 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_1500uS  (0x5 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_1750uS  (0x6 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_2000uS  (0x7 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_2250uS  (0x8 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_2500uS  (0x9 << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_2750uS  (0xA << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_3000uS  (0xB << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_3250uS  (0xC << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_3500uS  (0xD << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_3750uS  (0xE << NRF24_ARD_POS)
#define NRF24_SETUP_RETR_ARD_4000uS  (0xF << NRF24_ARD_POS)

// ARC (Auto Retransmit Count) 
#define NRF24_SETUP_RETR_ARC_0		0x0
#define NRF24_SETUP_RETR_ARC_1		0x1
#define NRF24_SETUP_RETR_ARC_2		0x2
#define NRF24_SETUP_RETR_ARC_3		0x3
#define NRF24_SETUP_RETR_ARC_4		0x4
#define NRF24_SETUP_RETR_ARC_5		0x5
#define NRF24_SETUP_RETR_ARC_6		0x6
#define NRF24_SETUP_RETR_ARC_7		0x7
#define NRF24_SETUP_RETR_ARC_8		0x8
#define NRF24_SETUP_RETR_ARC_9		0x9
#define NRF24_SETUP_RETR_ARC_10		0xA
#define NRF24_SETUP_RETR_ARC_11		0xB
#define NRF24_SETUP_RETR_ARC_12		0xC
#define NRF24_SETUP_RETR_ARC_13		0xD
#define NRF24_SETUP_RETR_ARC_14		0xE
#define NRF24_SETUP_RETR_ARC_15		0xF

//DPL
#define NRF24_DPL_P5  5
#define NRF24_DPL_P4  4
#define NRF24_DPL_P3  3
#define NRF24_DPL_P2  2
#define NRF24_DPL_P1  1
#define NRF24_DPL_P0  0

//feature
#define NRF24_EN_DPL      2
#define NRF24_EN_ACK_PAY  1
#define NRF24_EN_DYN_ACK  0

typedef enum {
  Bit_RESET = 0,
  Bit_SET = 1
} BitAction;

//Data rate
//--------------------------------------------------------------
typedef enum{
    NRF24_DataRate_1M   = 0x00, // 00: 1 Mbps
    NRF24_DataRate_2M   = 0x08, // 08: 2 Mbps (бит 3 = 1)  
	NRF24_DataRate_250k = 0x20  // 20: 250 Kbps (бит 5 = 1)
} NRF24_DataRate_t;
//--------------------------------------------------------------

typedef enum {
	NRF24_OutputPower_M18dBm = 0x00,  // 00: -18dBm
	NRF24_OutputPower_M12dBm = 0x02,  // 02: -12dBm (бит 1 = 1)
	NRF24_OutputPower_M6dBm  = 0x04,  // 04: -6dBm  (бит 2 = 1)
	NRF24_OutputPower_0dBm   = 0x06   // 06: 0dBm   (биты 1+2 = 1)
} NRF24_OutputPower_t;


//                               REGISTERS
/*===============================================================================*/

//Config registers
//--------------------------------------------------------------
enum NRF24_ConfigReg{
	NRF24_REG_CONFIG      = 0x00, // Nado
	NRF24_REG_EN_AA       = 0x01, // Auto Acknowledgment for pipe
	NRF24_REG_EN_RXADDR   = 0x02, // Enable data pipe 0
	NRF24_REG_SETUP_AW    = 0x03, // Setting the address width
	NRF24_REG_SETUP_RETR  = 0x04, // Setting up retransmission
	NRF24_REG_RF_CH       = 0x05, // RF channels
	NRF24_REG_RF_SETUP    = 0x06, // Setting RF
	NRF24_REG_STATUS      = 0x07, // Status register
	NRF24_REG_OBSERVE_TX  = 0x08, 
	NRF24_REG_RPD         = 0x09,
	NRF24_REG_FIFO_STATUS = 0x17,
	NRF24_REG_DYNPD       = 0x1C,
	NRF24_REG_FEATURE     = 0x1D
};
enum nRF24_AddressReg{
  NRF24_REG_RX_ADDR_P0 = 0x0A, // receive address data pipe
  NRF24_REG_RX_ADDR_P1 = 0x0B,
  NRF24_REG_RX_ADDR_P2 = 0x0C,
  NRF24_REG_RX_ADDR_P3 = 0x0D,
  NRF24_REG_RX_ADDR_P4 = 0x0E,
  NRF24_REG_RX_ADDR_P5 = 0x0F,
  NRF24_REG_TX_ADDR    = 0x10  //Transmit address
};
typedef enum {
  NRF24_REG_RX_PW_P0 = 0x11, // Number of bytes in RX payload in data pipe 0 (1 to 32 bytes).
  NRF24_REG_RX_PW_P1 = 0x12, // Number of bytes in RX payload in data pipe 1
  NRF24_REG_RX_PW_P2 = 0x13, // Number of bytes in RX payload in data pipe 2
  NRF24_REG_RX_PW_P3 = 0x14, // Number of bytes in RX payload in data pipe 3
  NRF24_REG_RX_PW_P4 = 0x15, // Number of bytes in RX payload in data pipe 4
  NRF24_REG_RX_PW_P5 = 0x16  // Number of bytes in RX payload in data pipe 5
} NRF24_PacketSizeReg_t;
/*===============================================================================*/

//                                 BITS
/*===============================================================================*/
struct NRF24_REG_CONFIG_BITS {
  uint8_t PRIM_RX     : 1;  // Бит 0: RX/TX control (1=RX, 0=TX)
  uint8_t PWR_UP      : 1;  // Бит 1: Power up (1=Power Up, 0=Power Down)
  uint8_t CRCO        : 1;  // Бит 2: CRC encoding (0=1 byte, 1=2 bytes)
  uint8_t EN_CRC      : 1;  // Бит 3: Enable CRC (1=Enabled)
  uint8_t MASK_MAX_RT : 1;  // Бит 4: Mask MAX_RT interrupt (1=Masked)
  uint8_t MASK_TX_DS  : 1;  // Бит 5: Mask TX_DS interrupt (1=Masked)
  uint8_t MASK_RX_DR  : 1;  // Бит 6: Mask RX_DR interrupt (1=Masked)
  uint8_t reserved    : 1;  // Бит 7: Reserved
};
//--------------------------------------------------------------
typedef  union {
    struct NRF24_REG_CONFIG_BITS bit;
    uint8_t all;
} NRF24_CONFIG_REGISTER;

struct NRF24_REG_EN_AA_BITS{
	uint8_t ENAA_P0  : 1;
	uint8_t ENAA_P1  : 1;
	uint8_t ENAA_P2  : 1;
	uint8_t ENAA_P3  : 1;
	uint8_t ENAA_P4  : 1;
	uint8_t ENAA_P5  : 1;
	uint8_t reserved : 2;
};
typedef  union {
    struct NRF24_REG_EN_AA_BITS bit;
    uint8_t all;
} NRF24_EN_AA_REGISTER;
//--------------------------------------------------------------
struct NRF24_REG_EN_RXADDR_BITS{
	uint8_t ERX_P0   : 1;
	uint8_t ERX_P1   : 1;
	uint8_t ERX_P2   : 1;
	uint8_t ERX_P3   : 1;
	uint8_t ERX_P4   : 1;
	uint8_t ERX_P5   : 1;
	uint8_t reserved : 2;
};
typedef  union {
    struct NRF24_REG_EN_RXADDR_BITS bit;
    uint8_t all;
} NRF24_EN_RXADDR_REGISTER;

//--------------------------------------------------------------
struct NRF24_REG_SETUP_AW_BITS{
	uint8_t AW       : 2;
	uint8_t reserved : 6;
};
typedef  union {
    struct NRF24_REG_SETUP_AW_BITS bit;
    uint8_t all;
} NRF24_SETUP_AW_REGISTER;
//--------------------------------------------------------------

struct NRF24_SETUP_RETR_REG_BITS {
    uint8_t ARC  : 4; //0..3
    uint8_t ARDa : 4; //4..7
};
typedef  union {
    struct NRF24_SETUP_RETR_REG_BITS bit;
    uint8_t all;
} NRF24_SETUP_RETR_REGISTER;
//--------------------------------------------------------------
struct NRF24_REG_RF_CH_BITS{
	uint8_t RF_CH    : 7;
	uint8_t reserved : 1;
};
typedef  union {
    struct NRF24_REG_RF_CH_BITS bit;
    uint8_t all;
} NRF24_RF_CH_REGISTER;
//--------------------------------------------------------------

struct NRF24_REG_RF_SETUP_BITS{
	uint8_t Obsolete   : 1;
	uint8_t RF_PWR     : 2;
	uint8_t RF_DR_HIGH : 1;
	uint8_t PLL_LOCK   : 1;
	uint8_t RF_DR_LOW  : 1;
	uint8_t reserved   : 1;
	uint8_t COUNT_WAVE : 1;
};
typedef  union {
    struct NRF24_REG_RF_SETUP_BITS bit;
    uint8_t all;
} NRF24_RF_SETUP_REGISTER;

//--------------------------------------------------------------
struct NRF24_STATUS_REG_BITS {
  uint8_t TX_FULL   : 1;  // Бит 0: Data Ready RX FIFO
  uint8_t RX_P_NO   : 3;  // Бит 1: Data Sent TX FIFO  
  uint8_t MAX_RT  	: 1;  // Бит 2: Max Retransmits
  uint8_t TX_DS		: 1;  // Бит 3: Reserved
  uint8_t RX_DR 	: 1;  // Биты 4-6: Pipe Number for RX payload
  uint8_t reserved 	: 1;  // Бит 7: TX FIFO Full
};

typedef  union {
    struct NRF24_STATUS_REG_BITS bit;
    uint8_t all;
} NRF24_STATUS_REGISTER;

//--------------------------------------------------------------
struct NRF24_OBSERVE_TX_REG_BITS{
	uint8_t ARC_CNT  : 4;
	uint8_t PLOS_CNT : 4;
};
typedef  union {
    struct NRF24_OBSERVE_TX_REG_BITS bit;
    uint8_t all;
} NRF24_OBSERVE_TX_REGISTER;

//--------------------------------------------------------------
struct NRF24_RPD_REG_BITS{
	uint8_t RPD      : 1;
	uint8_t reserved : 7;
};
typedef  union {
    struct NRF24_RPD_REG_BITS bit;
    uint8_t all;
} NRF24_RPD_REGISTER;

//--------------------------------------------------------------

struct NRF24_FIFO_STATUS_REG_BITS{
	uint8_t RX_EMPTY 	: 1;
	uint8_t RX_FULL 	: 1;
	uint8_t reserved1   : 2;
	uint8_t TX_EMPTY 	: 1;
	uint8_t TX_FULL 	: 1;
	uint8_t TX_REUSE 	: 1;
	uint8_t reserved2   : 1;
};
typedef  union {
    struct NRF24_FIFO_STATUS_REG_BITS bit;
    uint8_t all;
} NRF24_FIFO_STATUS_REGISTER;
//--------------------------------------------------------------

struct NRF24_DYNPD_REG_BITS{
	uint8_t DPL_P0   : 1;
	uint8_t DPL_P1   : 1;
	uint8_t DPL_P2   : 1;
	uint8_t DPL_P3   : 1;
	uint8_t DPL_P4   : 1;
	uint8_t DPL_P5   : 1;
	uint8_t reserved : 1;
};
typedef  union {
    struct NRF24_DYNPD_REG_BITS bit;
    uint8_t all;
} NRF24_DYNPD_REGISTER;

//--------------------------------------------------------------

struct NRF24_FEATURE_REG_BITS{
	uint8_t EN_DYN_ACK : 1;
	uint8_t EN_ACK_PAY : 1;
	uint8_t EN_DPL     : 1;
	uint8_t reserved   : 5;
};
typedef  union {
    struct NRF24_FEATURE_REG_BITS bit;
    uint8_t all;
} NRF24_FEATURE_REGISTER;
/*===============================================================================*/

//                                 Commands
/*===============================================================================*/
enum NRF24_Commands{
	NRF24_CMD_R_REGISTER         = 0x00, // read command and status registers
	NRF24_CMD_W_REGISTER         = 0x20, // write command and status registers
	NRF24_CMD_R_RX_PAYLOAD       = 0x61, // read RX-payload
	NRF24_CMD_W_TX_PAYLOAD       = 0xA0, // write TX-payload
	NRF24_CMD_FLUSH_TX           = 0xE1, // Flush TX FIFO, used in TX mode
	NRF24_CMD_FLUSH_RX           = 0xE2, // Flush RX FIFO, used in RX mode
	NRF24_CMD_REUSE_TX_PL        = 0xE3, // Used for a PTX device. Reuse last transmitted payload
	NRF24_CMD_R_RX_PL_WID        = 0x60, // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
	NRF24_CMD_W_ACK_PAYLOAD      = 0xA8, // Used in RX mode. Write Payload to be transmitted together with ACK packet on PIPE PPP
	NRF24_CMD_W_TX_PAYLOAD_NOACK = 0xB0, // Used in TX mode. Disables AUTOACK on this specific packet.
	NRF24_CMD_NOP                = 0xFF  // No Operation. Might be used to read the STATUS register
};
/*==============================================================================*/

//                                  Functions
/*==============================================================================*/
void NRF24l01_init(void);
void NRF24_RX_mode(void);
void NRF24_TX_mode(void);
void NRF24_SendTX(uint8_t *data);
uint8_t NRF24_ReadReg(uint8_t rg); // read single register
void NRF24_WriteReg(uint8_t rg, uint8_t dt); // write single register
void NRF24_WriteBit(uint8_t rg, uint8_t bit, BitAction value); // write bit to nrf24 register
void NRF24_WritePayload(uint8_t *data, uint8_t data_size); // Write data to transmission
void NRF24_WriteRegMultiple(uint8_t reg, uint8_t *data, uint8_t len); 
void NRF24_ClearStatus(void);
void NRF24_FLUSH_RX(void);
void NRF24_FLUSH_TX(void);
void NRF24_RX_Config(void);
void NRF24_writeTX(uint8_t *data);
uint8_t NRF24_ReadRX(uint8_t *data, uint8_t data_size);
void NRF24_Set_rx_addr(uint8_t *addr, uint8_t num_pipe);
void NRF24_Set_tx_addr(uint8_t *addr);

//READ
NRF24_STATUS_REGISTER NRF24_ReadStatus();
NRF24_CONFIG_REGISTER NRF24_ReadConfig();
NRF24_EN_AA_REGISTER NRF24_Read_EN_AA();
NRF24_EN_RXADDR_REGISTER NRF24_Read_EN_RXADDR();
NRF24_SETUP_AW_REGISTER NRF24_Read_Setup_AW();
NRF24_SETUP_RETR_REGISTER NRF24_Read_Setup_RETR();
NRF24_RF_CH_REGISTER NRF24_Read_RF_CH();
NRF24_RF_SETUP_REGISTER NRF24_Read_RF_SETUP();
NRF24_OBSERVE_TX_REGISTER NRF24_Read_OBSERVE_TX();
NRF24_RPD_REGISTER NRF24_Read_RPD();
NRF24_FIFO_STATUS_REGISTER NRF24_Read_FIFO_STATUS();
NRF24_DYNPD_REGISTER NRF24_Read_DYNPD();
NRF24_FEATURE_REGISTER NRF24_Read_FEATURE();
#endif
