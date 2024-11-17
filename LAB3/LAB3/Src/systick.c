//#include "stm32f107xx.h"
//
//
//#define SYSTICK_LOAD_VAL		9000
//#define STCSR_CFG				(0x5<<0)
//#define STCSR_COUNTFLAG			(1U<<16)
//
//
//void systickDelayMs(int delay) // We create a function that's not going to somewhere else but if only if
//// turning back an integer n value
//{
//	//--Configure the Systick--//
//
//	//Reloads with number of clock per millisecond//
//	SysTick->LOAD = SYSTICK_LOAD_VAL;
//
//	//Clear Systick Current Value Register//
//	//Enable Systick and select internal clock source//
//	SysTick->VAL = 0;
//	SysTick->CTRL |= STCSR_CFG;
//
//	for (int i=0;i<delay;i++)
//	{
//		        // Wait until count flag is set
//		        while ((SysTick->CTRL & STCSR_COUNTFLAG) == 0);
//		    }
//
//	SysTick->CTRL = 0;
//}

