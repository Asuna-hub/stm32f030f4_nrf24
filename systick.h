#ifndef SYSTICK_H
#define SYSTICK_H

#include "main.h"

#define SYSCLOCK 48000000

extern uint32_t SysTick_CNT;

void SysTick_Init(void);
void delay_mS(uint32_t mS);

#endif