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
#include "taskbar.h"

const unsigned int TASKBARCURVE = 16;

const unsigned int TASKBARBORDERDARKERGRADIENTAMOUNT = 40;

void drawTaskbar(Framebuffer* framebuffer, TaskBar* taskbar)
{
    const unsigned int X = taskbar->bounds.pos.x; //The drawn x position of the window
    const unsigned int Y = taskbar->bounds.pos.y; //The drawn y position of the window
    const unsigned int WIDTH = taskbar->bounds.dimensions.width; //The drawn width
    const unsigned int HEIGHT = taskbar->bounds.dimensions.height; //The drawn height

    int i; //Declare int 'i' for looping
    //outlineGradientCurvedRect(framebuffer, x, y, width, height, TASKBARCURVE, taskbar->colour, changeBrightness(taskbar->colour, -40), true, true, false, false);
    fillOutlinedGradientCurvedRect(framebuffer, X, Y, WIDTH, HEIGHT, TASKBARCURVE, taskbar->colour, changeBrightness(taskbar->colour, -TASKBARBORDERDARKERGRADIENTAMOUNT), taskbar->colour, changeBrightness(taskbar->colour, -TASKBARBORDERDARKERGRADIENTAMOUNT), true, true, false, false); //Draw the title bar

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

    result.bounds.pos.x = (SCREENWIDTH - width) / 2;
    result.bounds.pos.y = SCREENHEIGHT - height; //Do not need to divide by 2 as you want the bar at the bottom of the screen
    result.bounds.dimensions.width = width;
    result.bounds.dimensions.height = height;
    result.colour = colour;

    return result;
}