#include "dataSize.h"
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "string.h"

const char units[6][4] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB"};


SizeUnitPair dataSize_standardize (size_t sizeInBytes) {
    double size = (double)sizeInBytes;
    int unit = 0;
    while (size >= 1024) {
        size /= 1024;
        unit++;
    }
    SizeUnitPair sizeUnitPair;
    sizeUnitPair.size = size;
    sizeUnitPair.unit = unit;
    return sizeUnitPair;
}

