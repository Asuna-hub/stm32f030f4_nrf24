#include "rcc.h"

void RCC_Init(void)
{
    RCC->CR |= RCC_CR_HSION;
    while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
    RCC->CR &= ~RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 1);
	
    // PLL = (HSI / 2) * 12 = (8 / 2) * 12 = 48
    RCC->CFGR &= ~(RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE);
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
    RCC->CFGR |= RCC_CFGR_PLLMUL12;

    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0);
    
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE); 

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}