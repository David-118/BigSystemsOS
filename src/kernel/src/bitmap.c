#include "bitmap.h"
#include "kernel.h"
#include <stdint.h>


bool bitmap_get(Bitmap* buffer, uint64_t i) 
{
    if (i > buffer->size * 8) {return false;}
    uint64_t index = i / 8;
    uint8_t bit = 0x80 >> (i % 8); 
    return ((buffer->buffer[index] & bit) > 0);
}


bool bitmap_set(Bitmap* buffer, uint64_t i, bool value) 
{    
    if (i > buffer->size * 8) {return false;}
    uint8_t bvalue = value * 0xff;
    uint64_t index = (i / 8);
    uint8_t bit = 0x80 >> (i % 8);
    buffer->buffer[index] = (buffer->buffer[index] & ~bit) | (bit & bvalue);
    return true;
}