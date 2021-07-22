#pragma once
#include <stddef.h>
#include <stdint.h>
#include "efiMemory.h"
#include "bitmap.h"
#include "memory.h"

void pageFrameAllocator_readEfiMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescriptorSize);
void pageFrameAllocator_freePage(void* address);
void pageFrameAllocator_lockPage(void* address);
void pageFrameAllocator_freePages(void* address, uint64_t pageCount);
void pageFrameAllocator_lockPages(void* address, uint64_t pageCount);

uint8_t* pageFrameAllocator_pageBitmap;
size_t pageFrameAllocator_pageBitmapSize;
