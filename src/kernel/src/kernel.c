
#include "kernel.h"




/**
 * 
 * JACOB HOW TO COMPILE YOU PLONKER
 * 
 * Paste this in unbuntu
 * make build-x86_64
 * 
 * Run "RUNOS.bat"
 * 
 */

/**
 * 
 */
void _start(BootInfo* bootInfo) 
{
    clearScreen(bootInfo->framebuffer, 0xffffffff);
    //Window makeWindow(char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)

    Window myWindow = makeWindow(bootInfo->framebuffer, "BEANS", 50, 50, 200, 200, false, false, true, true, 0xff000000, bootInfo->psf1_font, 0xffC3C3C3);
    drawWindow(bootInfo->framebuffer, &myWindow);

    //unsigned const BORDERWIDTH = 10;
    //fillOutlinedRect(bootInfo->framebuffer, 10, 10, 1200, 1000, BORDERWIDTH, 0xff909090, 0xff0000ff);

}

unsigned int stringLength(char* string)
{
    int count;
    count = 0;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}

char str_buffer[128];
const char* uint_to_string(unsigned int value)
{
    unsigned int size = 0;
    unsigned int sizeTest = value;

    while ((sizeTest / 10) > 0)
    {
        sizeTest /= 10;
        size++;
    }        
    int index = 0;
    while (value > 0)
    {
        str_buffer[size - index] = (value % 10) + '0';
        index++;
        value /= 10;
    }
    str_buffer[size + 1] = '\0';
    return str_buffer;
}

const char* int_to_string(int value)
{
    int size = 0;
    int sizeTest = value;

    while ((sizeTest / 10) != 0)
    {
        sizeTest /= 10;
        size++;
    }
    if (value < 0)
    {
        size += 1;
        str_buffer[0] = '-';
        value *= -1;
    }

    int index = 0;
    while (value > 0)
    {
        str_buffer[size - index] = (value % 10) + '0';
        index++;
        value /= 10;
    }
    str_buffer[size + 1] = '\0';
    return str_buffer;
}