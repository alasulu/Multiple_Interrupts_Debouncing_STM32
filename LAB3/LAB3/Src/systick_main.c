//#include <stdio.h>
//#include <stdint.h>
//#include "stm32f107xx.h"
//#include "systick.h"
//
//#define GPIOAEN 	(1U<<2)
//#define PIN5		(1U<<5)
//#define LED			 PIN5
//
//
//int main(void)
//{
//
//	//Enable clock acces for GPIOA
//	RCC->APB2ENR |= GPIOAEN;
//
//	//Set PA5 as output pin
//	GPIOA->CRL &= ~(0xF<<20);
//	GPIOA->CRL |= (0x1<<20);
//
//	while(1)
//	{
//		GPIOA->BSRR = LED;       // Set PA5 high
//		systickDelayMs(1000);    // Delay for 1 second
//		GPIOA->BSRR = (1U << 21); // Set PA5 low
//		systickDelayMs(1000);    // Delay for 1 second
//	}
//}
