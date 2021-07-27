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
#include "mousePointer.h"

bool isMouseInBounds(MousePointer* mousePointerPointer, Bounds* bounds)
{
    return isPointInBounds(&(mousePointerPointer->pos), bounds);
}

void drawMousePointer(Framebuffer* framebuffer, MousePointer* mousePointerPointer)
{
    //This is the code we'll want when we can allocate memory
    //drawImageToBuffer(framebuffer, mousePointerPointer->mouseImage, mousePointerPointer->pos.x, mousePointerPointer->pos.y); //Draw the mouse

    fillRect(framebuffer, mousePointerPointer->pos.x, mousePointerPointer->pos.y, 10, 10, 0xff000000); //Temporay code until I add some image to the mouse buffer
}

MousePointer makeMousePointer(unsigned int x, unsigned int y)
{
    MousePointer result;
    result.pos.x = x;
    result.pos.y = y;
    //result.mouseImage = SOMETHING //Add when I can asign/allocate memory
    return result;
}