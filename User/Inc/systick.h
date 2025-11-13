#ifndef SYSTICK_H
#define SYSTICK_H

#include "main.h"

#define SYSCLOCK 48000000

extern uint32_t SysTick_CNT;

void SysTick_Init(void);
void delay_uS(uint32_t uS);
void TIM3_Init(void);
void delay_s(uint32_t sec);

#endif