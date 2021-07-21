#include "gop.h"
#include "kernal.h"

void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) 
{
    //putChar(framebuffer, psf1_font, 0xffffffff, 'G', 10, 10);
    setPixel(framebuffer, 10, 10, 0xff0000ff);

}

void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour) {
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
     *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
}


void putChar(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff) 
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->PSF1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++) {
        for (unsigned long x = xOff; x < xOff + 8; x++) {
            
            if ((*fontPtr & (0b1000000 >> (x-xOff))) > 0) {
                *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
            }

        }
        fontPtr++;
    }
}