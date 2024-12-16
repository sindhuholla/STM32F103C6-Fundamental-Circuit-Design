#include "main.h"
// Timer initialization for PWM
void Timer2_Init(void) {
    RCC->APB1ENR |= (1 << 0);  // Enable TIM2 clock
    TIM2->PSC = 71;  // (72 MHz / (71 + 1)) = 1 MHz (1 µs period)
    TIM2->ARR = 999;  // Set auto-reload register for 1 kHz PWM frequency
    TIM2->CCR2 = 0;  // Initial duty cycle is 0 (LED off)
    TIM2->CCMR1 &= ~(0xFF << 8);  // Clear settings for Channel 2
    TIM2->CCMR1 |= (0x6 << 12);  // Set PWM mode on Channel 2
    TIM2->CCER |= (1 << 4);  // Enable PWM output on Channel 2 (PA1)
    TIM2->CR1 |= (1 << 0);  // Enable Timer 2
}

// Delay function (in ms)
void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        TIM2->CNT = 0;  // Reset the timer counter (CNT)
        while (!(TIM2->SR & (1 << 0))); // Wait for the update flag (UIF)
        TIM2->SR &= ~(1 << 0);  // Clear the update interrupt flag (UIF)
    }
}
