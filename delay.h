#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

void delay_us(__IO uint32_t nTime);

void TimingDelay_Decrement(void);
void delay_config();
#endif
