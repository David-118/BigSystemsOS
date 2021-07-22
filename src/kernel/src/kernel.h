#pragma once


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
void clearScreen(Framebuffer* framebuffer, unsigned int colour);
void drawhar(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void drawString(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff);
void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour);
void fillRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour);
void fillOutlinedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour);
void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour);
void drawline(Framebuffer* framebuffer, int x0, int y0, int x1, int y1, unsigned int colour);