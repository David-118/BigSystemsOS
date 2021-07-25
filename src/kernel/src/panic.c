#include "panic.h"
#include "graphics.h"
#include "panic.h"

Framebuffer* framebuffer;
PSF1_FONT* font;
void panic_init(BootInfo* bootInfo) {
    framebuffer = bootInfo->framebuffer;
    font = bootInfo->psf1_font;
}

void panic_panic(const char *message) {
    clearScreen(framebuffer,makeColour(0, 0, 255, 255));
    drawString(framebuffer, font, makeColour(255, 255, 255, 255), message, 16, 16);
    while(true);
}