/*
 * Copyright © 2021 BIG SYSTEMS INC
 *
 * This file is part of BIG SYSTEMS OS.
 *
 * BIG SYSTEMS OS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Public License Version 2 as published
 * by the Free Software Foundation.
 *
 * BIG SYSTEMS OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "memory.h"
#include <stdint.h>

/*
* Get total memory in bytes
*/
uint64_t memory_getSize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize) 
{
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) {return memorySizeBytes;}

    for (uint64_t i = 0; i < mMapEntries; i++) 
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        memorySizeBytes += desc->numPages * 4096;
    }
    return memorySizeBytes;
}

void memory_memset(void* start, uint8_t value, uint64_t bytes)
{
    for (uint64_t i = 0; i < bytes; i++) 
    {
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}