#include "kernel.h"
#include "boot_info.h"
#include "efiMemory.h"
#include "kernel.h"
#include "memory.h"
#include "bitmap.h"
#include "pageFrameAllocator.h"
#include <stdint.h>



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
 extern uint64_t _KernelStart;
 extern uint64_t _KernelEnd;
void _start(BootInfo* bootInfo) 
{

    pageFrameAllocator_readEfiMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages  = kernelSize / 4096 + 1;
    
    pageFrameAllocator_lockPages((void*)&_KernelStart, kernelPages);

    

    clearScreen(bootInfo->framebuffer, 0xffffe0ff);
    //Window makeWindow(char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)

    Window myWindow = makeWindow(bootInfo->framebuffer, "BEANS", 50, 50, 200, 200, false, false, true, true, 0xff000000, bootInfo->psf1_font, makeColour(200, 200, 220, 215));
    TaskBar myTaskBar = makeTaskbar(bootInfo->framebuffer, 1024, 128, makeColour(200, 200, 220, 215));
    drawWindow(bootInfo->framebuffer, &myWindow);
    drawTaskbar(bootInfo->framebuffer, &myTaskBar);

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
const char* uint_to_string(uint64_t value)
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

const char* int_to_string(int64_t value)
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

const char* ubyte_to_bin(uint8_t value) 
{
    str_buffer[8] = '\0';
    for (int i = 7; i >= 0; i--) {
        str_buffer[i] =  (value & 1) + '0';
        value >>=1;
    }
    return str_buffer;
}
