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
#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../efiMemory.h"
#include "../bitmap.h"
#include "../memory.h"

void pageFrameAllocator_readEfiMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescriptorSize);
void pageFrameAllocator_freePage(void* address);
void pageFrameAllocator_lockPage(void* address);
void pageFrameAllocator_freePages(void* address, uint64_t pageCount);
void pageFrameAllocator_lockPages(void* address, uint64_t pageCount);
void* pageFrameAllocator_requestPage();

uint64_t pageFrameAllocator_getFreeRAM();
uint64_t pageFrameAllocator_getUsedRAM();
uint64_t pageFrameAllocator_getReservedRAM();


Bitmap* pageFrameAllocator_getPageBitmap();