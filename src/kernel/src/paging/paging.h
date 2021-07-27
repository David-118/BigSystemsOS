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
#include <stdbool.h>
#include <stdint.h>

enum PT_Flag
{
    present = 0,
    readWrite = 1,
    UserSuper = 2,
    WriteThrough = 3,
    CacheDisabled = 4,
    Accessed = 5,
    LargerPages = 7,
    Custom0 = 9,
    Custom1 = 10,
    Custom2 = 11,
    NX = 63, //ONLY SUPPORTED ON SOME SYSTEMS
};

typedef uint64_t PageDirEntry;

void paging_setFlag(PageDirEntry* PDE, enum PT_Flag flag, bool enabled);
bool paging_getFlag(PageDirEntry* PDE, enum PT_Flag flag);
void paging_setAddress(PageDirEntry* PDE, uint64_t address);
uint64_t paging_getAddress(PageDirEntry* PDE);

typedef struct  __attribute__((aligned(0x1000)))
{
    PageDirEntry entries [512];
} PageTable;

