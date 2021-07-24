#pragma once

#include <stdint.h>
#include "efiMemory.h"

uint64_t memory_getSize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize);
void memory_memset(void* start, uint8_t value, uint64_t bytes);
