#include "taskbar.h"

const unsigned int TASKBARCURVE = 16;

const unsigned int TASKBARBORDERDARKERGRADIENTAMOUNT = 40;

void drawTaskbar(Framebuffer* framebuffer, TaskBar* taskbar)
{
    unsigned int x = taskbar->x; //The drawn x position of the window
    unsigned int y = taskbar->y; //The drawn y position of the window
    unsigned int width = taskbar->width; //The drawn width
    unsigned int height = taskbar->height; //The drawn height

    int i; //Declare int 'i' for looping
    //outlineGradientCurvedRect(framebuffer, x, y, width, height, TASKBARCURVE, taskbar->colour, changeBrightness(taskbar->colour, -40), true, true, false, false);
    fillOutlinedGradientCurvedRect(framebuffer, x, y, width, height, TASKBARCURVE, taskbar->colour, changeBrightness(taskbar->colour, -TASKBARBORDERDARKERGRADIENTAMOUNT), taskbar->colour, changeBrightness(taskbar->colour, -TASKBARBORDERDARKERGRADIENTAMOUNT), true, true, false, false); //Draw the title bar

    //Draw buttons
    //(add rules for when there are no borders later)
    for (i = 0; i < 0; i++)
    {
        //Add way of drawing to taskbar
        //drawButton(framebuffer, window, &(taskbar->buttons[i])); //Draw a button
    }
}

TaskBar makeTaskbar(Framebuffer* framebuffer, unsigned int width, unsigned int height, unsigned int colour)
{
    TaskBar result;

    const unsigned int SCREENWIDTH = framebuffer->PixelsPerScanLine;
    const unsigned int SCREENHEIGHT = framebuffer->Height;

    result.x = (SCREENWIDTH - width) / 2;
    result.y = SCREENHEIGHT - height; //Do not need to divide by 2 as you want the bar at the bottom of the screen
    result.width = width;
    result.height = height;
    result.colour = colour;

    return result;
}