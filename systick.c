#include "systick.h"

uint32_t SysTick_CNT = 0;

void SysTick_Init(void){
	SysTick->LOAD = (SYSCLOCK / 1000) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void){
  if (SysTick_CNT > 0)
    SysTick_CNT--;
}

void delay_mS(uint32_t mS){
	SysTick->VAL = 0;
	SysTick->VAL = (SYSCLOCK / 1000) - 1;
	SysTick_CNT = mS;
	while(SysTick_CNT);
}