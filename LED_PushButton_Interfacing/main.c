#include "stm32f10x.h"                  // Device header for STM32F103

// Delay function that introduces a small delay
void delay(void){
    int i;
    for(i = 0; i < 1000000; i++);    // Simple delay loop
}

int main(){
    // Enable GPIOA peripheral clock
    RCC->APB2ENR |= 0x04;

    // Configure GPIOA pins:
    // - A1 as output for LED
    // - A2 as input for push button
    GPIOA->CRL = 0xFF000FFF;   // Clear configuration for A1 and A2
    GPIOA->CRL |= 0x000333000; // Set A1 as output (for LED)
    GPIOA->CRL |= 0x00000800;  // Set A2 as input (for push button)

    while(1){
        // Check if the push button (A2) is pressed
        if((GPIOA->IDR & (1 << 2))){
            // If button is pressed, blink LEDs on A3, A4, A5
            for(int i = 3; i < 6; i++){
                GPIOA->ODR |= (1 << i);  // Turn on the LED
                delay();                  // Wait for a while
                GPIOA->ODR &= ~(1 << i); // Turn off the LED
            }
        }    
    }
}

