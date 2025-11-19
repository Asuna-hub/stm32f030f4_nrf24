#include "dma.h"

void DMA_SPI_Init(void){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	
	DMA1_Channel2->CCR |= DMA_CCR_MINC; //incremente memory mode enable
	DMA1_Channel2->CCR &= ~DMA_CCR_MSIZE; // memory size - 8 bit
	DMA1_Channel2->CCR &= ~DMA_CCR_PSIZE; // Peripheral size - 8 bit
	DMA1_Channel2->CCR |= DMA_CCR_TCIE; // transfer complete interrupt enable
	DMA1_Channel2->CPAR = (uint32_t)&SPI1->DR;
	
	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
	
	DMA1_Channel3->CCR |= DMA_CCR_DIR;
	DMA1_Channel3->CCR |= DMA_CCR_MINC;
	DMA1_Channel3->CCR &= ~DMA_CCR_MSIZE; // memory size - 8 bit
	DMA1_Channel3->CCR &= ~DMA_CCR_PSIZE; // Peripheral size - 8 bit
	DMA1_Channel3->CCR |= DMA_CCR_TCIE;
	DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
	
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
} 



void DMA1_Channel2_3_IRQHandler(void){
	if (DMA1->ISR & DMA_ISR_TCIF2){
		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR = DMA_IFCR_CTCIF2;
	}
	if (DMA1->ISR & DMA_ISR_TCIF3){
		DMA1_Channel3->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR = DMA_IFCR_CTCIF3;
	}
}

void SPI_DMA_transfer_data(uint8_t *tx_data, uint8_t *rx_data, uint16_t size){
	DMA1->IFCR = DMA_IFCR_CTCIF3 | DMA_IFCR_CTCIF2 | 
				 DMA_IFCR_CHTIF3 | DMA_IFCR_CHTIF2 | 
				 DMA_IFCR_CTEIF3 | DMA_IFCR_CTEIF2;
	
	DMA1_Channel3->CMAR = (uint32_t)tx_data;
	DMA1_Channel3->CNDTR = size;
	
	DMA1_Channel2->CMAR = (uint32_t)rx_data;
	DMA1_Channel2->CNDTR = size;
	
}
	
void SPI_DMA_RX_TX_ON(void){
	SPI1->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;
}

void SPI_DMA_RX_TX_OFF(void){
	SPI1->CR2 &= ~(SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
}

void DMA_RX_TX_ON(void){
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	DMA1_Channel2->CCR |= DMA_CCR_EN;
}
