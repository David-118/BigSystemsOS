#pragma once
#include <stdint.h>

typedef struct {
    double size;
    int unit;
} SizeUnitPair;

extern const char units[6][4];

SizeUnitPair dataSize_standardize(uint64_t sizeInBytes);