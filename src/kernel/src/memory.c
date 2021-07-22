#include "memory.h"
#include <stdint.h>

/*
* Get total memory in bytes
*/
uint64_t memory_getSize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize) {
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) {return memorySizeBytes;}

    for (uint64_t i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;
}