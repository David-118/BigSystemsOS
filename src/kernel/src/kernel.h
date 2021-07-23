#pragma once
#include <stdint.h>
#include "boot_info.h"

typedef struct {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
}BootInfo;


void _start(BootInfo* bootInfo);
const char* uint_to_string(uint64_t value);
const char* int_to_string(int64_t value);
const char* ubyte_to_bin(uint8_t value);
const char* uint_to_hex(uint64_t value);
unsigned int stringLength(char* string);

