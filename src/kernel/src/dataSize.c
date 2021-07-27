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
#include "dataSize.h"
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "string.h"

const char units[6][4] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB"};


SizeUnitPair dataSize_standardize (size_t sizeInBytes)
{
    double size = (double)sizeInBytes;
    int unit = 0;
    while (size >= 1024)
    {
        size /= 1024;
        unit++;
    }
    SizeUnitPair sizeUnitPair;
    sizeUnitPair.size = size;
    sizeUnitPair.unit = unit;
    return sizeUnitPair;
}

