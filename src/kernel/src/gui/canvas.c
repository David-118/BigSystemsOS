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
#pragma once
#include "canvas.h"
#include "bounds.h"

void drawCanvas(Framebuffer* framebuffer, Canvas* canvas, Window* window)
{
    unsigned int x = getCanvasActualX(canvas, window); //The drawn x position of the window
    unsigned int y = getCanvasActualY(canvas, window); //The drawn y position of the window
    unsigned int width = canvas->bounds.dimensions.width; //The drawn width
    unsigned int height = canvas->bounds.dimensions.height; //The drawn height

    //Draw the canvas image
}
Point geCanvasActualPos(Window* window, Canvas* canvas)
{
    const Point WINDOWPOS = getWindowPos(window);
    return getPosRelativeTo(&WINDOWPOS, &(canvas->bounds.pos));
}

void makeCanvas()
{
    //Allocate memory for drawing to the screen
}