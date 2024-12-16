#include "stm32f10x.h"

void uart_init(void)
{
    // Enable USART1 and GPIOA clocks
    RCC->APB2ENR = 0x00004004;  // USART1EN = 1, IOPAEN = 1

    // Configure PA9 (TX) as Alternate Function Push-Pull, Output 2 MHz
    GPIOA->CRH = 0x000004B0;    // MODE9 = 0b10, CNF9 = 0b10 (TX)

    // USART1 Configuration: Baud rate = 9600, Enable TX, RX, and USART
    USART1->BRR = 0x1D4C;       // Baud rate 9600 for 72 MHz PCLK2
    USART1->CR1 = 0x00002008;   // UE = 1, TE = 1 (Only Transmit Enabled)
}

void uart_transmit(char *data)
{
    while (*data)
    {
        while (!(USART1->SR & 0x80)); // Wait until TXE (bit 7) is empty
        USART1->DR = *data++;        // Transmit character
    }
}

int main(void)
{
    uart_init(); // Initialize UART

    while (1)
    {
        uart_transmit("ON\r\n"); // Send 'ON' string
        for (volatile int i = 0; i < 1000000; i++); // Simple delay
    }
}
