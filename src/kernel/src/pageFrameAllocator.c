#include "pageFrameAllocator.h"
#include "efiMemory.h"
#include "memory.h"
#include "bitmap.h"
#include "kernel.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool initialized = false;

uint8_t* pageFrameAllocator_pageBitmap;
size_t pageFrameAllocator_pageBitmapSize;




void initBitmap(void* addr, size_t size) 
{
    // Intilize Bitmap
    pageFrameAllocator_pageBitmap = (uint8_t*) addr;
    pageFrameAllocator_pageBitmapSize = size;
    

    for (uint64_t i = 0; i < size; i++) {
        *(uint8_t*)(pageFrameAllocator_pageBitmap + i) = 0;
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

void pageFrameAllocator_readEfiMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescriptorSize) 
{
    if (initialized) {return;}

    initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescriptorSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (uint64_t i = 0; i < mMapEntries; i++) {
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

    uint64_t pageBitmapSize = memorySize / 4096 / 8 + 1;
    initBitmap(largestFreeMemSeg, pageBitmapSize);
    

    pageFrameAllocator_lockPages(&pageFrameAllocator_pageBitmap, pageFrameAllocator_pageBitmapSize / 4096 + 1);
    
    for (uint64_t i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        if (desc->type != EfiConventionalMemory) {
            pageFrameAllocator_reservePages(desc->physAddr, desc->numPages);
        }
    }

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

void pageFrameAllocator_lockPages(void *address, uint64_t pageCount) {
    for (uint64_t i = 0; i < pageCount; i++) {
        pageFrameAllocator_lockPage((void*)((uint64_t) address + (i * 4096)));
    }
}

void* pageFrameAllocator_requestPage() {
    uint64_t row = 0, col=0;
    for (uint64_t index = 0; index < pageFrameAllocator_pageBitmapSize * 8; index++) {
        if (bitmap_get(pageFrameAllocator_pageBitmap, index) == true) {continue;}

        pageFrameAllocator_lockPage((void*)(index * 4096));
        return (void*) (index * 4096);
    }   

    return NULL; // Page Frame to swap to file
}

uint64_t pageFrameAllocator_getFreeRAM(){
    return freeMemory;
}
uint64_t pageFrameAllocator_getUsedRAM(){
    return usedMemory;
}
uint64_t pageFrameAllocator_getReservedRAM(){
    return reservedMemory;
}

uint8_t* pageFrameAllocator_getPageBitmap() {
    return pageFrameAllocator_pageBitmap;
}

size_t pageFrameAllocator_getPageBitmapSize() {
    return pageFrameAllocator_pageBitmapSize;
}

