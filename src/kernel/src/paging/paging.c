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
#include "paging.h"
#include <stdint.h>


void paging_setFlag(PageDirEntry* PDE, enum PT_Flag flag, bool enabled) 
{
    uint64_t bitSelector = (uint64_t)1 << flag;
    *PDE =  (*PDE &~bitSelector) | (bitSelector & (uint64_t)enabled * 0XFFFFFFFFFFFFFFFF );
}

bool paging_getFlag(PageDirEntry *PDE, enum PT_Flag flag) {
    uint64_t bitSelector = (uint64_t)1 << flag;
    return (*PDE & bitSelector) > 0;
}

uint64_t paging_getAddress(PageDirEntry *PDE) {
    return (*PDE & 0x000ffffffffff000) >> 12;
}

void paging_setAddress(PageDirEntry *PDE, uint64_t address) {
    address &= 0x000000ffffffffff;
    *PDE &= ~0x000ffffffffff000;
    *PDE |= address << 12;

}