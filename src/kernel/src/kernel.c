
#include <stdint.h>
#include <string.h>
#include "paging/pageMapIndexer.h"
#include "windowManager.h"
#include "guistructures.h"
#include "graphics.h"
#include "taskbar.h"
#include "efiMemory.h"
#include "paging/pageFrameAllocator.h"
#include "memory.h"
#include "kernel.h"
#include "dataSize.h"
#include "paging/paging.h"
#include "paging/pageTableManager.h"

/*
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
void kernel_init();


void _start(BootInfo* bootInfo) 
{
    kernel_init();
    //clearScreen(bootInfo->framebuffer, 0xffffe0ff);
    //writeImage(bootInfo->framebuffer);
    /*
    Replace this with the desktop background
    */
    clearScreen(bootInfo->framebuffer, makeColour(127, 255, 212, 255));
    fillRect(bootInfo->framebuffer, 0, 980, 1920, 100, makeColour(50, 255, 50, 255));
    fillCircle(bootInfo->framebuffer, 0, 0, 0, 0, 80, 80, 80, makeColour(255, 255, 0, 255));
    //Window makeWindow(char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)

    Window myWindow = makeWindow(bootInfo->framebuffer, "BEANS", 50, 50, 200, 200, false, false, true, true, 0xff000000, bootInfo->psf1_font, makeColour(200, 200, 220, 215));
    TaskBar myTaskBar = makeTaskbar(bootInfo->framebuffer, 1024, 128, makeColour(200, 200, 220, 215));
    drawWindow(bootInfo->framebuffer, &myWindow);
    drawTaskbar(bootInfo->framebuffer, &myTaskBar);

    //unsigned const BORDERWIDTH = 10;
    //fillOutlinedRect(bootInfo->framebuffer, 10, 10, 1200, 1000, BORDERWIDTH, 0xff909090, 0xff0000ff);
    
    while (true); //stops ths os from dying
}

// Setsup memory
void kernel_init(BootInfo* bootInfo) {
    pageFrameAllocator_readEfiMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages  = kernelSize / 4096 + 1;
    
    pageFrameAllocator_lockPages((void*)&_KernelStart, kernelPages);


    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;    
    
    PageTable* PML4 = (PageTable*)pageFrameAllocator_requestPage();


    PageMapIndex pageIndex = PageMapIndexer__virtualAddress(4096 * 52 + 0x50000 * 7);
    

    memory_memset(PML4, 0 , 4096);

    for (uint64_t i = 0; i < memory_getSize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); i+=4096) {
        pageTableManager_mapMemory(PML4, (void*)i, (void*)i);
    }
    
    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 4096;
    pageFrameAllocator_lockPages((void*) fbBase, fbSize / 4096 + 1);

    for (uint64_t i = fbBase; i < fbBase + fbSize; i += 4096) {
         pageTableManager_mapMemory(PML4, (void*)i, (void*)i);
    }


    // Places the page table pointer in a special regester using assembly
    asm("mov %0, %%cr3" :: "r" (PML4));
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
    if (value==0) {return "0";}
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

const char* double_to_string(double value, uint8_t decimalPlaces){
    if (decimalPlaces > 20) decimalPlaces = 20;

    char* intPtr = (char*)int_to_string((int64_t)value);
    char* doublePtr = str_buffer;

    if (value < 0){
        value *= -1;
    }

    while(*intPtr != 0){
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for (uint8_t i = 0; i < decimalPlaces; i++){
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;
    return str_buffer;
}


const char* int_to_string(int64_t value)
{
    if (value==0) {return "0";}
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


