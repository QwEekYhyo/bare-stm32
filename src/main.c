#include <stdint.h>

// Not true time
void delay(uint32_t time) {
    for (uint32_t i = 0; i < time; i++)
        for (uint32_t j = 0; j < time; j++) {}
}

uint32_t app_ticks = 0;

volatile uint8_t blinky_enable = 1;

uint32_t last_led_blink = 0;

int main(void) {
    // Enable RCC for GPIOB
    *((volatile uint32_t*) 0x4002104C) |= 1 << 1;

    // Enable RCC for SYSCFG
    *((volatile uint32_t*) 0x40021060) |= 1 << 0;

    // Set PB8 as output (0b01)
    *((volatile uint32_t*) 0x48000400) |= 1 << 16;
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 17);

    // Set PB0 as input (0b00)
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 0);
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 1);

    // Enable line 0 in EXTI Interrupt Mask register
    *((volatile uint32_t*) 0x40010400) |= 1 << 0;
    // Configure trigger selection
    *((volatile uint32_t*) 0x40010408) |= 1 << 0;
    // idk SYSCFG EXTICR1 EXTI0
    *((volatile uint32_t*) 0x40010008) |= 0b0001 << 0;
    // NVIC_ISER0 enable EXTI0
    *((volatile uint32_t*) 0xE000E100) |= 1 << 6;

    for (;;) {
        if (blinky_enable && app_ticks >= last_led_blink + 0x10000) {
            last_led_blink = app_ticks;
            // Switch LED state
            *((volatile uint32_t*) 0x48000414) ^= 1 << 8;
        }

        app_ticks++;
    }

    return 0;
}

void exti0_irq_handler(void) {
    // Check interrupt Pending Register
    uint32_t interrupt_state = *((volatile uint32_t*) 0x40010414);
    if (interrupt_state & 1) {
        // Clear interrupt Pending Register
        *((volatile uint32_t*) 0x40010414) = 1 << 0;
        blinky_enable = !blinky_enable;
        // Turn off LED
        *((volatile uint32_t*) 0x48000414) &= ~(1 << 8);
    }
}
