#include "canvas.h"

void drawCanvas(Framebuffer* framebuffer, Canvas* canvas, Window* window)
{
    unsigned int x = getCanvasActualX(canvas, window); //The drawn x position of the window
    unsigned int y = getCanvasActualY(canvas, window); //The drawn y position of the window
    unsigned int width = canvas->width; //The drawn width
    unsigned int height = canvas->height; //The drawn height

    //Draw the canvas image
}

unsigned int getCanvasActualX(Window* window, Canvas* canvas)
{
    return getWindowX(window)+canvas->relativeX;
}

unsigned int getCanvasActualY(Window* window, Canvas* canvas)
{
    return getWindowY(window)+canvas->relativeY;
}