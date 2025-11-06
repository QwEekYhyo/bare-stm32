#include <stdint.h>

int main(void) {
    *((volatile uint32_t*) 0x4002104C) |= 1 << 1;

    *((volatile uint32_t*) 0x48000400) |= 1 << 16;
    *((volatile uint32_t*) 0x48000400) &= ~(1 << 17);

    *((volatile uint32_t*) 0x48000414) |= 1 << 8;

    for (;;) {
    }

    return 0;
}
