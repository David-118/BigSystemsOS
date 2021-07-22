
#include "windowManager.h"


const unsigned int WINDOWBORDERWIDTH = 5; //The border width of the window

const unsigned int WINDOWTITLEBARHEIGHT = 30; //The height of the window's forehead (oh boy his hairline is bad)

const unsigned int WINDOWBASEFILLCOLOUR = 0xffd0d0d0; //The default background colour of a window (before anythings been drawn)... we'll probably remove this later


void drawWindow(Framebuffer* framebuffer, Window* window)
{
    unsigned int x = getWindowX(window); //The drawn x position of the window
    unsigned int y = getWindowY(window); //The drawn y position of the window
    unsigned int width = getWindowWidth(framebuffer, window); //The drawn width
    unsigned int height = getWindowHeight(framebuffer, window); //The drawn height

    int i; //Declare int 'i' for looping

    if (window->isMinimised == false)
    { //If the window isn't minimised
        if (window->hasBorders == true)
        { //If the window has outline borders
            fillRect(framebuffer, x, y, width, WINDOWTITLEBARHEIGHT, window->borderColour); //Draw the title bar
            const unsigned int XOFFSET = 5;
            const unsigned int YOFFSET = 5;
            drawString(framebuffer, window->font, window->textColour, window->NAME, XOFFSET+window->x, YOFFSET+window->y); //Draw the title text
            fillOutlinedRect(framebuffer, x, y+WINDOWTITLEBARHEIGHT, width, height-WINDOWTITLEBARHEIGHT, WINDOWBORDERWIDTH, WINDOWBASEFILLCOLOUR, window->borderColour); //Draw a window with borders 
        }
        else
        { //If the window does not have outline borders
            fillRect(framebuffer, x, y, width, height, WINDOWBASEFILLCOLOUR); //Draw a window without borders
        }
        //Draw buttons
        //(add rules for when there are no borders later)
        for (i = 0; i < 3; i++)
        {
            drawButton(framebuffer, window, &(window->buttons[i])); //Draw a button
        }
    }
}
/**
 * Bassically a constructor cause simpleton Jacob can't live without his OOP 
 * (He might die of a quintuple stroke and double heart-attack if you remove this so please don't)
 */
Window makeWindow(Framebuffer* framebuffer, char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour)
{
    Window result;
    result.NAME = NAME;
    result.x = x;
    result.y = y;
    result.width = width;
    result.height = height;
    result.isFullScreen = isFullScreen;
    result.isMinimised = isMinimised;
    result.isResizable = isResizable;
    result.hasBorders = hasBorders;
    result.textColour = textColour;
    result.font = font;
    result.borderColour = borderColour;

    const unsigned int BUTTONSIZE = 24;
    const unsigned int BUTTONXSTEP = 30;
    const unsigned int BUTTONOFFSET = (WINDOWTITLEBARHEIGHT - BUTTONSIZE) / 2;
    const unsigned int BUTTONY = BUTTONOFFSET;
    const unsigned int BUTTONSTARTX = getWindowWidth(framebuffer, &result) - WINDOWBORDERWIDTH - BUTTONSIZE;

    int i; //Declare int 'i' for looping

    for (i = 0; i < 3; i++)
    {
        result.buttons[i] = makeButton("X", BUTTONSTARTX-(i*BUTTONXSTEP), BUTTONY, BUTTONSIZE, BUTTONSIZE, 0xffe00000, 0xff900000, 0xff000000, font);
    }

    return result;
}

void updateTitleBarButtonPosition(Framebuffer* framebuffer, Window* window)
{
    const unsigned int BUTTONSIZE = 24;
    const unsigned int BUTTONXSTEP = 30;
    const unsigned int BUTTONOFFSET = (WINDOWTITLEBARHEIGHT - BUTTONSIZE) / 2;
    const unsigned int BUTTONY = BUTTONOFFSET;
    const unsigned int BUTTONSTARTX = getWindowWidth(framebuffer, window) - WINDOWBORDERWIDTH - BUTTONSIZE;

    int i; //Declare int 'i' for looping

    for (i = 0; i < 3; i++)
    {
        window->buttons[i].relativeX = BUTTONSTARTX-(i*BUTTONXSTEP);
        window->buttons[i].relativeY = BUTTONY;
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
    window->width = width;
    window->height = height;
    updateTitleBarButtonPosition(framebuffer, window);
}

void moveWindow(Window* window, unsigned int x, unsigned int y)
{
    window->x = x;
    window->y = y;
}

unsigned int getWindowWidth(Framebuffer* framebuffer, Window* window)
{
    if (window->isFullScreen == true)
    {
        return framebuffer->PixelsPerScanLine;
    }
    else
    {
        return window->width;
    }
}

unsigned int getWindowHeight(Framebuffer* framebuffer, Window* window)
{
    if (window->isFullScreen == true)
    {
        return framebuffer->Height;
    }
    else
    {
        return window->height;
    }
}

unsigned int getWindowX(Window* window)
{
    if (window->isFullScreen == true)
    {
        return 0;
    }
    else
    {
        return window->x;
    }
}

unsigned int getWindowY(Window* window)
{
    if (window->isFullScreen == true)
    {
        return 0;
    }
    else
    {
        return window->y;
    }
}