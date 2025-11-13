#include "systick.h"

uint32_t SysTick_CNT = 0;

void SysTick_Init(void){
	SysTick->LOAD = (SYSCLOCK / 1000000) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void){
	if (SysTick_CNT > 0)
		SysTick_CNT--;
}

void delay_uS(uint32_t uS){
	SysTick->VAL = 0;
	SysTick->VAL = (SYSCLOCK / 1000000) - 1;
	SysTick_CNT = uS;
	while(SysTick_CNT);
}


void TIM3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 47999;
    TIM3->ARR = 999;

    TIM3->CR1 |= TIM_CR1_URS;
    TIM3->EGR |= TIM_EGR_UG;
}

void delay_s(uint32_t sec) {
    TIM3->CR1 &= ~TIM_CR1_CEN;
    TIM3->CNT = 0;
    TIM3->SR &= ~TIM_SR_UIF;

    TIM3->CR1 |= TIM_CR1_CEN;

    for (uint32_t i = 0; i < sec; i++) {
        while (!(TIM3->SR & TIM_SR_UIF));
        TIM3->SR &= ~TIM_SR_UIF;
    }
    TIM3->CR1 &= ~TIM_CR1_CEN;
}
