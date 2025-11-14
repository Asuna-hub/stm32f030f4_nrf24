#include "dma.h"

void DMA_SPI_Init(void){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	
	DMA1_Channel2->CCR |= DMA_CCR_MINC; //incremente memory mode enable
	DMA1_Channel2->CCR &= ~DMA_CCR_MSIZE; // memory size - 8 bit
	DMA1_Channel2->CCR &= ~DMA_CCR_PSIZE; // Peripheral size - 8 bit
	DMA1_Channel2->CCR |= DMA_CCR_CIRC; // Circular mode enable
	DMA1_Channel2->CCR |= DMA_CCR_TCIE; // transfer complete interrupt enable
	
	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
	
	DMA1_Channel3->CCR |= DMA_CCR_DIR;
	DMA1_Channel3->CCR |= DMA_CCR_MINC;
	DMA1_Channel3->CCR &= ~DMA_CCR_MSIZE; // memory size - 8 bit
	DMA1_Channel3->CCR &= ~DMA_CCR_PSIZE; // Peripheral size - 8 bit
	DMA1_Channel3->CCR |= DMA_CCR_TCIE;
	
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
} 


void SPI_DMA_Transmit(uint8_t data, uint16_t size)
{
    while(DMA1_Channel3->CCR & DMA_CCR_EN);
    
    DMA1->IFCR |= DMA_IFCR_CTCIF3 | DMA_IFCR_CHTIF3 | DMA_IFCR_CGIF3;
    
    DMA1_Channel3->CMAR = (uint32_t)data; 
    DMA1_Channel3->CPAR = (uint32_t)&(SPI1->DR);
    DMA1_Channel3->CNDTR = size;
    
    DMA1_Channel3->CCR |= DMA_CCR_EN;

    SPI1->CR2 |= SPI_CR2_TXDMAEN;
}

void SPI_DMA_Receive(uint8_t buffer, uint16_t size)
{
    while(DMA1_Channel2->CCR & DMA_CCR_EN);
    
    DMA1->IFCR |= DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CGIF2;
    
    DMA1_Channel2->CMAR = (uint32_t)buffer;
    DMA1_Channel2->CPAR = (uint32_t)&(SPI1->DR);
    DMA1_Channel2->CNDTR = size;
    
    DMA1_Channel2->CCR |= DMA_CCR_EN;
    
    SPI1->CR2 |= SPI_CR2_RXDMAEN;
}

