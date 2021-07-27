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
#include <stdint.h>
#include "boot_info.h"

typedef struct
{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
}BootInfo;

void _start(BootInfo* bootInfo);
const char* uint_to_string(uint64_t value);
const char* int_to_string(int64_t value);
const char* double_to_string(double value, uint8_t decimalPlaces);
const char* ubyte_to_bin(uint8_t value);
const char* uint_to_hex(uint64_t value);
char* concat(const char* str1, const char* str2);
unsigned int stringLength(char* string);



