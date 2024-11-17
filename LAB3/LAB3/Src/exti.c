#include "exti.h"
#include "stm32f107xx.h"
#define GPIOAEN 		(0x1<<2)
#define GPIOBEN			(0x1<<3)
#define AFIOEN			(0x1<<0)
#define IMR0			(0x1<<0)
#define IMR2			(0x1<<2)
#define RTSR0			(0x1<<0)
#define RTSR2			(0x1<<2)
#define PINA0		(0x1<<0)
#define LEDA0		(PINA0)
#define PINA1		(0x1<<1)
#define LEDA1		(PINA1)


void exti_init(void){

	//Disable Global Interrupts
	__disable_irq();
	//Enable Clock Access to Ports
	RCC->APB2ENR |= GPIOAEN; // Enable RCC reach to GPIOA Ports with Advance Peripheral Bus 2 [Input Configuration]
	RCC->APB2ENR |= GPIOBEN;

	//Set PA0 and PA1 as input
	GPIOA->CRL &= ~(0xF<<0);
	GPIOA->CRL |= (0x2<<2); // PA0 Input with pull-up / pull-down
	GPIOB->CRL &= ~(0xF<<8);
	GPIOB->CRL |= (0x2<<10); // PB2 Input with pull-up / pull-down

	/*Our EXTI is a part of SYSCONFIG (SYSCFG) module, so we need to enable access for that module
	as well In F1 Series, we need to enable the AFIO bit in the RCC_APB2ENR Register*/
	RCC->APB2ENR |= AFIOEN;

	//Select PORTA for EXTI0 (Input Interrupt Setup)
	AFIO->EXTICR[0] &= ~(0xF<<0); //Selection of the source input for EXTI0 external interrupt. (0000: PA[x] pin)

	//Select PORTA for EXTI1 (Input Interrupt Setup)
	AFIO->EXTICR[0] &= ~(0xF<<8); //Selection of the source input for EXTI2 external interrupt. (0001: PB[x] pin)
	AFIO->EXTICR[0] |= (0x1<<8);

	//Unmask EXTI0
	EXTI->IMR |= IMR0; //It means "Interrupt request from Line 0 is not masked (ignored)"

	//Unmask EXTI2
	EXTI->IMR |= IMR2; //It means "Interrupt request from Line 2 is not masked (ignored)"

	/*Decide whether input interrupts will be triggered by rising edge or falling edge.
	Over here we will use rising edge trigger*/
	EXTI->RTSR |= RTSR0; // Rising trigger enabled (for Event and Interrupt) for input line 0.
	EXTI->RTSR |= RTSR2; // Rising trigger enabled (for Event and Interrupt) for input line 2.

	//Set Priority between buttons
	  //PORTA0 has more priority than PORTA1
	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	//Enable Global Interrupts
	__enable_irq();

}
