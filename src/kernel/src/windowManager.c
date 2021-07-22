#include "boot_info.h"
#include "kernel.h"
#include "windowManager.h"
#include "stdbool.h"

const unsigned int WINDOWBORDERWIDTH = 10; //The border width of the window

const unsigned int WINDOWBASEFILLCOLOUR = 0xff909090; //The default background colour of a window (before anythings been drawn)... we'll probably remove this later

const unsigned int WINDOWBASEBORDERCOLOUR = 0xff0000ff; //The default border colour of a window

void drawWindow(Framebuffer* framebuffer, Window* window)
{
    unsigned int x = getWindowX(window); //The drawn x position of the window
    unsigned int y = getWindowY(window); //The drawn y position of the window
    unsigned int width = getWindowWidth(framebuffer, window); //The drawn width
    unsigned int height = getWindowHeight(framebuffer, window); //The drawn height
    if (window->isMinimised == false)
    {
        if (window->hasBorders == true)
        { //If the window has outline borders
            fillOutlinedRect(framebuffer, x, y, width, height, WINDOWBORDERWIDTH, WINDOWBASEFILLCOLOUR, WINDOWBASEBORDERCOLOUR); //Draw a window with borders 
        }
        else
        { //If the window does not have outline borders
            fillRect(framebuffer, x, y, width, height, WINDOWBASEFILLCOLOUR); //Draw a window without borders
        }
    }
    
}
/**
 * Bassically a constructor cause simpleton Jacob can't live without his OOP 
 * (He might die of a quintuple stroke and double heart-attack if you remove this so please don't)
 */
Window* makeWindow(char* NAME[50], int x, int y, int width, int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders)
{
    Window result;
    //result.NAME = NAME;
    result.x = x;
    result.y = y;
    result.width = width;
    result.height = height;
    result.isFullScreen = isFullScreen;
    result.isMinimised = isMinimised;
    result.isResizable = isResizable;
    result.hasBorders = hasBorders;

}

void resizeWindow(Window* window, unsigned int width, unsigned int height)
{
    window->isFullScreen = false;
    window->width = width;
    window->height = height;
}

void moveWindow(Window* window, unsigned int x, unsigned int y)
{
    window->x = x;
    window->y = y;
}

unsigned int getWindowWidth(Framebuffer* framebuffer, Window* window)
{
    if (window->isFullScreen)
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
    if (window->isFullScreen)
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
    if (window->isFullScreen)
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
    if (window->isFullScreen)
    {
        return 0;
    }
    else
    {
        return window->y;
    }
}