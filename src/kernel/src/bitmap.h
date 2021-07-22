#pragma once
#include <stdbool.h>
#include <stdint.h>

void bitmap_set(uint8_t* buffer, uint64_t i, bool value);
bool bitmap_get(uint8_t* buffer, uint64_t i);

