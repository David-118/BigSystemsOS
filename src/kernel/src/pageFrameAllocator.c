#include "pageFrameAllocator.h"
#include "efiMemory.h"
#include "memory.h"
#include "bitmap.h"
#include <stddef.h>
#include <stdint.h>

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool initialized = false;


uint8_t* initBitmap(void* addr, size_t size) 
{
    // Intilize Bitmap
    uint8_t* bitmap = (uint8_t*) addr;

    for (uint64_t i = 0; i < size; i++) {
        *(uint8_t*)(bitmap + i) = 0;
    }

    // Lock Pages were bitmap is stored
    // Reserve Pages for unusable/reserved memory

    return bitmap;

}

void pageFrameAllocator_readEfiMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescriptorSize) 
{
    if (initialized) {return;}

    initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescriptorSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + i * mMapDescriptorSize);
        if (desc->type == EfiConventionalMemory) {
            if (desc -> numPages * 4096 > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = memory_getSize(mMap, mMapEntries, mMapDescriptorSize);
    freeMemory = memorySize;

    pageFrameAllocator_pageBitmapSize = memorySize / 4096 / 8 + 1;
    pageFrameAllocator_pageBitmap = initBitmap(largestFreeMemSeg, pageFrameAllocator_pageBitmapSize);
    

}

void pageFrameAllocator_freePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(pageFrameAllocator_pageBitmap, index) == false) {return;}
    
    bitmap_set(pageFrameAllocator_pageBitmap, index, false);
    freeMemory+= 4096;
    usedMemory-= 4096;
}

void pageFrameAllocator_lockPage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(pageFrameAllocator_pageBitmap, index) == true) {return;}
    
    bitmap_set(pageFrameAllocator_pageBitmap, index, true);
    freeMemory-= 4096;
    usedMemory+= 4096;
}

void pageFrameAllocator_freePages(void *address, uint64_t pageCount) {
    for (uint64_t i = 0; i < pageCount; i++) {
        pageFrameAllocator_freePage((void*)((uint64_t) address + (i * 4096)));
    }
}

void pageFrameAllocator_lcokPages(void *address, uint64_t pageCount) {
    for (uint64_t i = 0; i < pageCount; i++) {
        pageFrameAllocator_lockPage((void*)((uint64_t) address + (i * 4096)));
    }
}

void pageFrameAllocator_unreservePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(pageFrameAllocator_pageBitmap, index) == false) {return;}
    
    bitmap_set(pageFrameAllocator_pageBitmap, index, false);
    freeMemory+= 4096;
    reservedMemory-= 4096;
}

void pageFrameAllocator_reservePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(pageFrameAllocator_pageBitmap, index) == true) {return;}
    
    bitmap_set(pageFrameAllocator_pageBitmap, index, true);
    freeMemory-= 4096;
    reservedMemory+= 4096;
}

void pageFrameAllocator_reservePages(void *address, uint64_t pageCount) {
    for (uint64_t i = 0; i < pageCount; i++) {
        pageFrameAllocator_reservePage((void*)((uint64_t) address + (i * 4096)));
    }
}

void pageFrameAllocator_unreservePages(void *address, uint64_t pageCount) {
    for (uint64_t i = 0; i < pageCount; i++) {
        pageFrameAllocator_unreservePage((void*)((uint64_t) address + (i * 4096)));
    }
}