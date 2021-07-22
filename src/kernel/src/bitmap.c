#include "bitmap.h"
#include "kernel.h"
#include <stdint.h>


bool bitmap_get(uint8_t* buffer, uint64_t i) {
    uint64_t index = i / 8;
    uint8_t bit = 0x80 >> (i % 8); 
    return ((buffer[index] & bit) > 0);
}


void bitmap_set(uint8_t* buffer, uint64_t i, bool value) {
    uint8_t bvalue = value * 0xff;
    uint64_t index = (i / 8);
    uint8_t bit = 0x80 >> (i % 8);
    buffer[index] = (buffer[index] & ~bit) | (bit & bvalue);
}