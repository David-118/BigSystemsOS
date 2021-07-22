#include "boot_info.h"
#include "kernel.h"
#include "windowManager.h"
#include "stdbool.h"

void drawWindow(Framebuffer* framebuffer, Window* win)
{
    const BORDERWIDTH = 10;
    fillOutlinedRect(framebuffer, win->x, win->y, win->Width, win->Height, BORDERWIDTH, 0xff909090, 0xff0000ff);
}

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