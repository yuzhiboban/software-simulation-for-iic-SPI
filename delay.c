#include"delay.h"
static __IO uint32_t TimingDelay;

void delay_config(){
		if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1);
  }
}

void delay_us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
