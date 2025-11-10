#include <stdint.h>

// Not true time
void delay(uint32_t time) {
    for (uint32_t i = 0; i < time; i++)
        for (uint32_t j = 0; j < time; j++) {}
}

uint32_t app_ticks = 0;

uint8_t blinky_enable = 0;
uint8_t button_state;
uint8_t last_button_state;

uint32_t last_led_blink = 0;

int main(void) {
    // Enable RCC for GPIOB
    *((volatile uint32_t*) 0x4002104C) |= 1 << 1;

    // Set PB8 as output (0b01)
    *((volatile uint32_t*) 0x48000400) |= 1 << 16;
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 17);

    // Set PB0 as input (0b00)
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 0);
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 1);

    // Set PUPDR0 to 0b01 (pull-up)
    *((volatile uint32_t*) 0x4800040C) |= 1 << 0;
    *((volatile uint32_t*) 0x4800040C) &= ~(1 << 1);

    last_button_state = !(*((volatile uint32_t*) 0x48000410) & 1);

    for (;;) {
        button_state = !(*((volatile uint32_t*) 0x48000410) & 1);

        // This somewhat works
        if (!button_state && last_button_state) {
            blinky_enable = !blinky_enable;
            // Turn off LED
            *((volatile uint32_t*) 0x48000414) &= ~(1 << 8);
        }

        last_button_state = button_state;

        if (blinky_enable && app_ticks >= last_led_blink + 0x10000) {
            last_led_blink = app_ticks;
            // Switch LED state
            *((volatile uint32_t*) 0x48000414) ^= 1 << 8;
        }

        app_ticks++;
    }

    return 0;
}
