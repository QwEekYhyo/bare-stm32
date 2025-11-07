#include <stdint.h>

// Not true time
void delay(uint32_t time) {
    for (uint32_t i = 0; i < time; i++)
        for (uint32_t j = 0; j < time; j++) {}
}

int main(void) {
    // Enable RCC for GPIOB
    *((volatile uint32_t*) 0x4002104C) |= 1 << 1;

    // Set PB8 as output (0b01)
    *((volatile uint32_t*) 0x48000400) |= 1 << 16;
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 17);

    for (;;) {
        // PB8 HIGH
        *((volatile uint32_t*) 0x48000414) |= 1 << 8;
        delay(1000);

        // PB8 LOW
        *((volatile uint32_t*) 0x48000414) &= ~(1 << 8);
        delay(1000);
    }

    return 0;
}
