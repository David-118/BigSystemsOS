
#include <stdint.h>
#include <string.h>

#include "kernelInit.h"

#include "windowManager.h"
#include "guistructures.h"
#include "graphics.h"
#include "taskbar.h"
#include "kernel.h"
#include "memory/heap.h"
#include "panic.h"

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

BootInfo* g_bootInfo;

void _start(BootInfo* bootInfo) 
{
    g_bootInfo = bootInfo;
    kernelInit(bootInfo);
    //clearScreen(bootInfo->framebuffer, 0xffffe0ff);
    //writeImage(bootInfo->framebuffer);
    /*
    Replace this with the desktop background
    */

    //Causes a page fault kernel panic
    // int* x = (int*) 0x800000000;
    // *x = 2;

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

    panic_debug(uint_to_hex((uint64_t)malloc(0x8000)));

    void* address = malloc(0x8000);
    panic_debug(uint_to_hex((uint64_t)address));
    panic_debug(uint_to_hex((uint64_t)malloc(0x100)));

    free(address);


    panic_debug(uint_to_hex((uint64_t)malloc(0x8000)));





    while (true); //stops the os from dying
}

// Setsup memory



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
    uint64_t size = 0;
    uint64_t sizeTest = value;

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

const char HEX_NIBBLES[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char* uint_to_hex(uint64_t value)
{
    if (value==0) {return "0";}
    uint64_t size = 0;
    uint64_t sizeTest = value;

    while ((sizeTest >> 4) > 0)
    {
        sizeTest >>= 4;
        size++;
    }

    int index = 0;
    while (value > 0)
    {
        str_buffer[size - index] = HEX_NIBBLES[value % 16];
        index++;
        value >>= 4;
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


