#include <stdbool.h>
#include "interrupts.h"
#include "../graphics.h"
#include "../kernel.h"


__attribute__((interrupt)) void pageFault_handler(struct interrupt_frame* frame){
    clearScreen(g_bootInfo->framebuffer, makeColour(0, 0, 255, 255));
    drawString(g_bootInfo->framebuffer, g_bootInfo->psf1_font, makeColour(255, 255, 255, 255), "Page Fault Detected", 16, 16);
    while(true);
}