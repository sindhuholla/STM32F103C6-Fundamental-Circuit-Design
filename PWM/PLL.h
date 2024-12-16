#include "main.h"
// Function to initialize PLL for 72 MHz system clock

void PLL_Init(void) {
    RCC->CR |= (1 << 16);  // Enable HSE (High-Speed External oscillator)
    while (!(RCC->CR & (1 << 17)));  // Wait for HSE to be ready
    RCC->CFGR |= (1 << 16);  // Set PLL source to HSE (8 MHz crystal)
    RCC->CFGR &= ~(0x7 << 18);  // Clear PLL multiplier bits
    RCC->CFGR |= (0x8 << 18);  // Set PLL multiplier to 9 (8 MHz * 9 = 72 MHz)
    RCC->CR |= (1 << 24);  // Enable PLL
    while (!(RCC->CR & (1 << 25)));  // Wait for PLL to be ready
    RCC->CFGR |= (0x2 << 0);  // Select PLL as system clock
    while ((RCC->CFGR & (0x3 << 2)) != (0x2 << 2));  // Wait until PLL is selected as SYSCLK
}