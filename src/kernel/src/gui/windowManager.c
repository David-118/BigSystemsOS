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
#include "windowManager.h"


const unsigned int WINDOWBORDERWIDTH = 4; //The border width of the window

const unsigned int WINDOWTITLEBARHEIGHT = 30; //The height of the window's forehead (oh boy his hairline is bad)

const unsigned int WINDOWDEFAULTFILLCOLOUR = 0xffeeeeee; //The default background colour of a window (before anythings been drawn)... we'll probably remove this later
//const unsigned int WINDOWDEFAULTBORDERCOLOUR = makeColor(200, 200, 200, 255); //The default background colour of a window (before anythings been drawn)... we'll probably remove this later

const unsigned int WINDOWBORDERDARKERGRADIENTAMOUNT = 40;


void drawWindow(Framebuffer* framebuffer, Window* window)
{

    Bounds bounds = getWindowBounds(framebuffer, window);

    unsigned int x = bounds.pos.x; //The drawn x position of the window
    unsigned int y = bounds.pos.y; //The drawn y position of the window
    unsigned int width = bounds.dimensions.width; //The drawn width
    unsigned int height = bounds.dimensions.height; //The drawn height



    int i; //Declare int 'i' for looping

    if (window->isMinimised == false)
    { //If the window isn't minimised
        if (window->hasBorders == true)
        { //If the window has outline borders
            fillOutlinedCurvedRect(framebuffer, x, y, width, WINDOWTITLEBARHEIGHT, WINDOWBORDERWIDTH, window->borderColour, window->borderColour, true, true, false, false); //Draw the title bar

            //fillRect(framebuffer, x, y, width, WINDOWTITLEBARHEIGHT, window->borderColour); //Draw the title bar
            const unsigned int XOFFSET = 5;
            const unsigned int YOFFSET = 5;
            drawString(framebuffer, window->font, window->textColour, window->NAME, XOFFSET+window->bounds.pos.x, YOFFSET+window->bounds.pos.y); //Draw the title text
            fillOutlinedGradientCurvedRect(framebuffer, x, y+WINDOWTITLEBARHEIGHT, width, height-WINDOWTITLEBARHEIGHT, WINDOWBORDERWIDTH, WINDOWDEFAULTFILLCOLOUR, WINDOWDEFAULTFILLCOLOUR, window->borderColour, changeBrightness(window->borderColour, -WINDOWBORDERDARKERGRADIENTAMOUNT), false, false, true, true); //Draw a window with borders 
        }
        else
        { //If the window does not have outline borders
            fillRect(framebuffer, x, y, width, height, WINDOWDEFAULTFILLCOLOUR); //Draw a window without borders
        }
        //Draw buttons
        //(add rules for when there are no borders later)
        for (i = 0; i < 3; i++)
        {
            drawButton(framebuffer, window, &(window->buttons[i])); //Draw a button
        }
    }
}

const unsigned int BUTTONXSTEP = 24; //Stores the gap between the 3 buttons on the title bar

/**
 * Bassically a constructor cause simpleton Jacob can't live without his OOP 
 * (He might die of a quintuple stroke and double heart-attack if you remove this so please don't)
 */
Window makeWindow(Framebuffer* framebuffer, char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)
{
    Window result;
    result.NAME = NAME;
    result.bounds.pos.x = x;
    result.bounds.pos.y = y;
    result.bounds.dimensions.width = width;
    result.bounds.dimensions.height = height;
    result.isFullScreen = isFullScreen;
    result.isMinimised = isMinimised;
    result.isResizable = isResizable;
    result.hasBorders = hasBorders;
    result.textColour = textColour;
    result.font = font;
    result.borderColour = borderColour;

    const unsigned int BUTTONSIZE = 20;
    const unsigned int BUTTONOFFSET = (WINDOWTITLEBARHEIGHT - BUTTONSIZE) / 2;
    const unsigned int BUTTONY = BUTTONOFFSET;


    Dimensions dimensions = getWindowDimensions(framebuffer, &result);
    const unsigned int BUTTONSTARTX = dimensions.width - WINDOWBORDERWIDTH - BUTTONSIZE;

    int i; //Declare int 'i' for looping

    for (i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            result.buttons[i] = makeButton("X", BUTTONSTARTX-(i*BUTTONXSTEP), BUTTONY, BUTTONSIZE, BUTTONSIZE, 0xffC84B4B, 0xffB03535, 0xff000000, font);
        }
        else if (i == 1)
        {
            result.buttons[i] = makeButton("O", BUTTONSTARTX-(i*BUTTONXSTEP), BUTTONY, BUTTONSIZE, BUTTONSIZE, 0xff99D9EA, 0xff79CEE3, 0xff000000, font);
        }
        else if (i == 2)
        {
            result.buttons[i] = makeButton("-", BUTTONSTARTX-(i*BUTTONXSTEP), BUTTONY, BUTTONSIZE, BUTTONSIZE, 0xffF0EA75, 0xffDAD570, 0xff000000, font);
        }
    }

    return result;
}

void updateTitleBarButtonPosition(Framebuffer* framebuffer, Window* window)
{

    Dimensions dimensions = getWindowDimensions(framebuffer, window);

    const unsigned int BUTTONSIZE = window->buttons[0].bounds.dimensions.height;
    const unsigned int BUTTONOFFSET = (WINDOWTITLEBARHEIGHT - BUTTONSIZE) / 2;
    const unsigned int BUTTONY = BUTTONOFFSET;
    const unsigned int BUTTONSTARTX = dimensions.width - WINDOWBORDERWIDTH - BUTTONSIZE;

    int i; //Declare int 'i' for looping

    for (i = 0; i < 3; i++)
    {
        window->buttons[i].bounds.pos.x = BUTTONSTARTX-(i*BUTTONXSTEP);
        window->buttons[i].bounds.pos.y = BUTTONY;
    }
}

void setFullScreen(Framebuffer* framebuffer, Window* window, bool isFullScreen)
{
    window->isFullScreen = isFullScreen;
    updateTitleBarButtonPosition(framebuffer, window);
}

void setMinimised(Window* window, bool isMinimised)
{
    window->isMinimised = isMinimised;
}

void resizeWindow(Framebuffer* framebuffer, Window* window, unsigned int width, unsigned int height)
{
    window->isFullScreen = false;
    window->bounds.dimensions.width = width;
    window->bounds.dimensions.height = height;
    updateTitleBarButtonPosition(framebuffer, window);
}

void moveWindow(Window* window, unsigned int x, unsigned int y)
{
    moveBound(&(window->bounds), x, y);
}

Bounds getWindowBounds(Framebuffer* framebuffer, Window* window)
{
    Bounds result;
    result.dimensions = getWindowDimensions(framebuffer, window);
    result.pos = getWindowPos(window);
    return result;
}
Dimensions getWindowDimensions(Framebuffer* framebuffer, Window* window)
{
    Dimensions result; 
    if (window->isFullScreen == true)
    {
        result.width = framebuffer->PixelsPerScanLine;
        result.height = framebuffer->Height;
    }
    else
    {
        result.width = window->bounds.dimensions.width;
        result.height = window->bounds.dimensions.height;
    }
    return result;
}

Point getWindowPos(Window* window)
{
    Point result; 
    if (window->isFullScreen == true)
    {
        result.x = 0;
        result.y = 0;
    }
    else
    {
        result.x = window->bounds.pos.x;
        result.y = window->bounds.pos.y;
    }
    return result;
}