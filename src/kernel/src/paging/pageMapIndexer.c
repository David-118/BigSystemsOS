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
#include "pageMapIndexer.h"

PageMapIndex PageMapIndexer__virtualAddress(uint64_t vAddress) {
    PageMapIndex this;
    vAddress >>= 12;
    this.P_i = vAddress & 0x1ff;
    
    vAddress >>= 9;
    this.PT_i = vAddress & 0x1ff;

    vAddress >>= 9;
    this.PD_i = vAddress & 0x1ff;

    vAddress >>= 9;
    this.PDP_i = vAddress & 0x1ff;
    
    return this;
}