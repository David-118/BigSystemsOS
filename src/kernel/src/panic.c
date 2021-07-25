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

// these function will be removed in the future
uint64_t row = 0, col = 0;
void panic_test() {
    drawString(framebuffer, font, makeColour(0, 0, 0, 255), "reached", col, row);
    row+=16;
}

void panic_debug(const char* message) {
     drawString(framebuffer, font, makeColour(0, 0, 0, 255), message, col, row);
    row+=16;
}