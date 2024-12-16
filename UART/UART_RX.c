#include "stm32f10x.h"

void uart_init(void)
{
    // Enable USART1 and GPIOA clocks
    RCC->APB2ENR = 0x00004004;  // USART1EN = 1 (bit 14), IOPAEN = 1 (bit 2)

    // Configure PA10 (RX) as Input Floating
    GPIOA->CRH = 0x00000400;    // CNF10 = 0b01 (Input Floating), MODE10 = 0b00 (Input)

    // USART1 Configuration: Baud rate = 9600, Enable TX, RX, and USART
    USART1->BRR = 0x1D4C;       // Baud rate 9600 for 72 MHz PCLK2
    USART1->CR1 = 0x0000200C;   // UE = 1 (bit 13), TE = 1 (bit 3), RE = 1 (bit 2)
}

void gpio_init(void)
{
    // Enable GPIOC clock
    RCC->APB2ENR |= 0x00000010;  // IOPCEN = 1 (bit 4)

    // Configure PC13 as Output Push-Pull, 2 MHz
    GPIOC->CRH &= (0xF0FFFFFF);   // Clear bits for PC13 (CNF13[1:0] = 00, MODE13[1:0] = 00)
    GPIOC->CRH |= (0x03000000);    // MODE13 = 0b10 (Output mode, 2 MHz)
}

char uart_receive(void)
{
    while (!(USART1->SR & 0x20)); // Wait until RXNE (bit 5) is set
    return (char)(USART1->DR);    // Read received data from Data Register
}

void toggle_led(void)
{
    GPIOC->ODR ^= (1 << 14); // Toggle PC13 (LED)
}

int main(void)
{
    uart_init();  // Initialize UART
    gpio_init();  // Initialize GPIO for LED control

    char received_char;
    char buffer[3]; // Buffer to store "ON"
    int idx = 0;

    while (1)
    {
        received_char = uart_receive(); // Receive a character
        buffer[idx++] = received_char;  // Store it in the buffer

        // If the complete "ON" string is received
        if (idx == 2 && buffer[0] == 'O' && buffer[1] == 'N')
        {
            toggle_led(); // Toggle LED
            idx = 0;      // Reset the buffer index
        }

        // Reset the buffer if newline or excess data is received
        if (idx >= 2 || received_char == '\n' || received_char == '\r')
        {
            idx = 0;
        }
    }
}
