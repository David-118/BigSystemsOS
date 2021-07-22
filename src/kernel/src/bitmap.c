#include "bitmap.h"
#include <stdint.h>


bool getBit(uint8_t* buffer, uint64_t i) {
    uint64_t index = i / 8;
    uint8_t bit = 0xFF >> i % 8; 
    return ((buffer[index] & bit) > 0);
}

void setBit(uint8_t *buffer, uint64_t i, bool value) {
    uint8_t bvaule = value ? 0 : 0xff;
    uint64_t index = i / 8;
    uint8_t bit = 0x80 >> i % 8; 
    buffer[index] = (buffer[index] & ~bit) | (bit & bvaule);
}