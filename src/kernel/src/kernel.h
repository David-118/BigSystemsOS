#pragma once
#include <stdint.h>
#include "boot_info.h"

typedef struct {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	void* mMap;
	long mMapSize;
	long mMapDescriptorSize;
}BootInfo;


void _start(BootInfo* bootInfo);
const char* uint_to_string(uint64_t value);
const char* int_to_string(int64_t value);
const char* ubyte_to_bin(uint8_t value);
const char* uint_to_hex(uint64_t value);

void clearScreen(Framebuffer* framebuffer, unsigned int colour);
void drawChar(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void drawString(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff);
void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour);
void fillRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour);
void fillOutlinedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour);
void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour);
void drawline(Framebuffer* framebuffer, int x0, int y0, int x1, int y1, unsigned int colour);

extern Framebuffer* framebuffer;
extern PSF1_FONT* psf1_font;