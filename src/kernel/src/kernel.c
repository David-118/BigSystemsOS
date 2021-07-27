/*
 * Copyright © 2021 BIG SYSTEMS INC
 *
 * This file is part of BIG SYSTEMS OS.
 *
 * BIG SYSTEMS OS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Public License Version 2 as published
 * by the Free Software Foundation.
 *
 * BIG SYSTEMS OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <string.h>

#include "kernelInit.h"

#include "gui/windowManager.h"
#include "gui/guistructures.h"
#include "gui/graphics.h"
#include "gui/taskbar.h"
#include "kernel.h"

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



void _start(BootInfo* bootInfo) 
{
    kernelInit(bootInfo);
    //clearScreen(bootInfo->framebuffer, 0xffffe0ff);
    //writeImage(bootInfo->framebuffer);
    /*
    Replace this with the desktop background
    */
    
    //Window makeWindow(char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)

    TaskBar myTaskBar = makeTaskbar(bootInfo->framebuffer, 1024, 128, makeColour(200, 200, 220, 215));

    clearScreen(bootInfo->framebuffer, makeColour(127, 255, 212, 255));
    fillRect(bootInfo->framebuffer, 0, 980, 1920, 100, makeColour(50, 255, 50, 255));
    fillCircle(bootInfo->framebuffer, 0, 0, 0, 0, 80, 80, 80, makeColour(255, 255, 0, 255));

    Window myWindow = makeWindow(bootInfo->framebuffer, "BEANS", 50, 50, 200, 200, false, false, true, true, 0xff000000, bootInfo->psf1_font, makeColour(200, 200, 220, 215));

    drawWindow(bootInfo->framebuffer, &myWindow);
    drawTaskbar(bootInfo->framebuffer, &myTaskBar);

    //unsigned const BORDERWIDTH = 10;
    //fillOutlinedRect(bootInfo->framebuffer, 10, 10, 1200, 1000, BORDERWIDTH, 0xff909090, 0xff0000ff);
    
    while (true); //stops ths os from dying
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


