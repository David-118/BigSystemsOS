#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    size_t size;
    uint8_t* buffer;
} Bitmap;

bool bitmap_set(Bitmap* buffer, uint64_t i, bool value);
bool bitmap_get(Bitmap* buffer, uint64_t i);

