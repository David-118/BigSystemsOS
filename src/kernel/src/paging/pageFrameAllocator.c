#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "pageFrameAllocator.h"
#include "../efiMemory.h"
#include "../memory.h"
#include "../bitmap.h"
#include "../kernel.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool initialized = false;

Bitmap pageFrameAllocator_pageBitmap;
uint64_t pageBitmapIndex = 0;


void initBitmap(void* addr, size_t size) 
{
    // Intilize Bitmap
    pageFrameAllocator_pageBitmap.buffer = (uint8_t*) addr;
    pageFrameAllocator_pageBitmap.size = size;
    

    for (uint64_t i = 0; i < size; i++) {
        *(uint8_t*)(pageFrameAllocator_pageBitmap.buffer + i) = 0;
    }

}

void pageFrameAllocator_unreservePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(&pageFrameAllocator_pageBitmap, index) == false) {return;}
    
    if (bitmap_set(&pageFrameAllocator_pageBitmap, index, false)) {
        freeMemory+= 4096;
        reservedMemory-= 4096;
        if (pageBitmapIndex > index) {pageBitmapIndex = index;}
    }
    
}

void pageFrameAllocator_reservePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(&pageFrameAllocator_pageBitmap, index) == true) {return;}
    
    if (bitmap_set(&pageFrameAllocator_pageBitmap, index, true)) {
        freeMemory-= 4096;
        reservedMemory+= 4096;
    }
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
    

    pageFrameAllocator_reservePages(0, memorySize / 0x1000 + 1);

    
    for (uint64_t i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        if (desc->type == EfiConventionalMemory) {
            pageFrameAllocator_unreservePages(desc->physAddr, desc->numPages);
        }
    }
    pageFrameAllocator_reservePages(0, 0x100); // Keeping the BIOS safe
    pageFrameAllocator_lockPages(&pageFrameAllocator_pageBitmap, pageFrameAllocator_pageBitmap.size / 4096 + 1);
}

void pageFrameAllocator_freePage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(&pageFrameAllocator_pageBitmap, index) == false) {return;}
    
    if (bitmap_set(&pageFrameAllocator_pageBitmap, index, false)){
        freeMemory+= 4096;
        usedMemory-= 4096;
        if (pageBitmapIndex > index) {pageBitmapIndex = index;}
    }
}

void pageFrameAllocator_lockPage(void *address) {
    uint64_t index = (uint64_t)address / 4096;
    if (bitmap_get(&pageFrameAllocator_pageBitmap, index) == true) {return;}
    
    if (bitmap_set(&pageFrameAllocator_pageBitmap, index, true)) {
        freeMemory-= 4096;
        usedMemory+= 4096;
    }
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
    for (; pageBitmapIndex < pageFrameAllocator_pageBitmap.size * 8; pageBitmapIndex++) {
        if (bitmap_get(&pageFrameAllocator_pageBitmap, pageBitmapIndex) == true) {continue;}

        pageFrameAllocator_lockPage((void*)(pageBitmapIndex * 4096));
        return (void*) (pageBitmapIndex * 4096);
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

Bitmap* pageFrameAllocator_getPageBitmap() {
    return &pageFrameAllocator_pageBitmap;
}

