#include <stdio.h>
#include <stdint.h>
#include "stm32f107xx.h"
#include "exti.h"

// Constants and macros
#define GPIOCEN           (0x1 << 4)
#define PINC13            (0x1 << 13)
#define LEDC13            (PINC13)
#define LEDC13_R          (0x1 << 29)
#define PINA0             (0x1 << 0)
#define LEDA0             (PINA0)
#define PINA1             (0x1 << 1)
#define LEDA1             (PINA1)
#define LINE0             (0x1 << 0)
#define LINE2             (0x1 << 2)
#define DEBOUNCE_DELAY_MS 1000
#define STCSR_COUNTFLAG			(1U<<16)

// Global variables
volatile uint32_t ms_ticks = 0;           // Millisecond counter
volatile uint32_t last_interrupt_time = 0; // Last interrupt time in ms

// Function declarations
void systick_init(void);
void exti_init(void);
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);
static void exti0_callback(void);
static void exti1_callback(void);

// Main function
int main(void) {
    // Enable GPIOC clock
    RCC->APB2ENR |= GPIOCEN;

    // Configure PC13 as output (max speed 10 MHz)
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (0x1 << 20);

    // Initialize SysTick and EXTI
    systick_init();
    exti_init();

    while (1) {
        // Main loop does nothing; interrupt handlers manage behavior
    }
}

// SysTick initialization for 1 ms ticks
void systick_init(void) {
    SysTick->LOAD = 9000; // 1 ms per tick
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

// SysTick handler to increment the ms_ticks counter
void SysTick_Handler(void) {
    ms_ticks++;
}

// Callback for EXTI0 interrupt (LED ON)
static void exti0_callback(void) {
    GPIOC->BSRR |= LEDC13; // Turn LED ON
}

// Callback for EXTI2 interrupt (LED OFF)
static void exti1_callback(void) {
    GPIOC->BSRR |= LEDC13_R; // Turn LED OFF
}

// EXTI0 interrupt handler
void EXTI0_IRQHandler(void) {
    if ((EXTI->PR & LINE0) != 0) { // Check if interrupt is from line 0
        uint32_t current_time = ms_ticks;
        if ((current_time - last_interrupt_time) > DEBOUNCE_DELAY_MS) {
            last_interrupt_time = current_time;
            EXTI->PR |= LINE0; // Clear pending interrupt flag
            exti0_callback();  // Call callback function
        }
    }
}

// EXTI2 interrupt handler
void EXTI2_IRQHandler(void) {
    if ((EXTI->PR & LINE2) != 0) { // Check if interrupt is from line 2
        uint32_t current_time = ms_ticks;
        if ((current_time - last_interrupt_time) > DEBOUNCE_DELAY_MS) {
            last_interrupt_time = current_time;
            EXTI->PR |= LINE2; // Clear pending interrupt flag
            exti1_callback();  // Call callback function
        }
    }
}
