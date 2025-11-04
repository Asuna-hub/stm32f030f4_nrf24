#include "spi.h"

volatile uint8_t nrf_irq_flag = 0;

void SPI1_Init(void){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //SPI clocking
	
	SPI1->CR1 = 0; //reset all CR1 registers
	SPI1->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0; // 48000000 / 8 = 6 MHz
	SPI1->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_RXONLY | SPI_CR1_BIDIOE); //2-line unidirectional data mode, full duplex
	SPI1->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA); //[0,0] mode (CPOL - 0, CPHA - 0)
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST; //MSB first
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; //Software slave management enable
	SPI1->CR1 |= SPI_CR1_MSTR; //Master configuration
	
	SPI1->CR2 = 0; //reset all CR2 registers
	SPI1->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2; // 8 bit 
	SPI1->CR2 |= SPI_CR2_FRXTH;
	
	SPI1->CR1 |= SPI_CR1_SPE; //SPI enable
}

void SPI1_NRF24_GPIO_Init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 
	GPIOA->AFR[0] = 0;
	
	//PA4 - NSS(CS), general purpose output push-pull
	GPIOA->MODER &= ~GPIO_MODER_MODER4_1;
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
	
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR4;
	
	GPIOA->BSRR = GPIO_BSRR_BS_4;
	
	//PA5 - SCK, AF output Push-pull
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
	
	//PA6 - MISO,
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	
	//PA7 - MOSI, AF output Push-pull
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER7_0;
	
	//PB1 - CE, general purpose output push-pull
	GPIOB->MODER &= ~GPIO_MODER_MODER1_1;
	GPIOB->MODER |= GPIO_MODER_MODER1_0;
	
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;
	
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR1;
	
	GPIOB->BSRR = GPIO_BSRR_BR_1;
	//PA0 - IRQ
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;
  GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0; // Pull-up
}

uint8_t SPI_transfer_data(uint8_t dt) {
  while (!(SPI1->SR & SPI_SR_TXE));
  *(__IO uint8_t*)&SPI1->DR = dt;
  while (!(SPI1->SR & SPI_SR_RXNE));
  return (*(__IO uint8_t*)&SPI1->DR);
}

void nrf_irq_init(void)
{
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	EXTI->RTSR &= ~EXTI_RTSR_TR0; 
	EXTI->FTSR |= EXTI_FTSR_TR0; 
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->PR = EXTI_PR_PR0;

	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR0)
	{
		EXTI->PR = EXTI_PR_PR0;
		nrf_irq_flag = 1;
	}
}
