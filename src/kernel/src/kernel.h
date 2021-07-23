#pragma once

#include "boot_info.h"
#include "windowManager.h"
#include "guistructures.h"
#include "graphics.h"
#include "taskbar.h"




typedef struct {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	void* mMap;
	long mMapSize;
	long mMapDescriptorSize;
}BootInfo;



void _start(BootInfo* bootInfo);
const char* uint_to_string(unsigned int value);
const char* int_to_string(int value);
unsigned int stringLength(char* string);
