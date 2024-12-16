#include "main.h"
#include "PLL.h"
#include "Timer.h"

// GPIO initialization for push button and LED
void GPIO_Init(void) {
    // Enable GPIOA clock
    RCC->APB2ENR |= (1 << 2);  // Enable clock for GPIOA

    // Configure PA1 as Alternate Function (LED with PWM)
    GPIOA->CRL &= ~(0xF << 4);   // Clear mode for PA1 (LED pin)
    GPIOA->CRL |= (0xB << 4);    // Set PA1 as Alternate Function Push-Pull for PWM control
}

int main() {
    int count = 0;  // Initialize the count value for PWM duty cycle

    PLL_Init();  // Initialize PLL to set the system clock to 72 MHz
    Timer2_Init();  // Initialize Timer2 for PWM signal generation on PA1 (LED)
    GPIO_Init();  // Initialize GPIO for button and LED control

    while (1) {
        count += 100;   // Increase PWM duty cycle by 100

        TIM2->CCR2 = count;  // Set the PWM duty cycle using Timer2's CCR2 register
        delay_ms(1000);      // Delay for 1 second to make the change noticeable

        if (count > 1000) {
            count = 0;  // Reset count back to 0 after it exceeds 1000
        }
    }
}
