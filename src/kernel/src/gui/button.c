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

#include "button.h"


const unsigned int BUTTONBORDERWIDTH = 4; //The border width of the window

Point geButtonActualPos(Window* window, Button* button)
{
    const Point WINDOWPOS = getWindowPos(window);
    return getPosRelativeTo(&WINDOWPOS, &(button->bounds.pos));
}

Bounds geButtonActualBounds(Window* window, Button* button)
{
    Bounds result;
    result.pos = geButtonActualPos(window, button);
    result.dimensions = button->bounds.dimensions;
    return result;
}

bool isMousePointerOverButton(MousePointer* mousePointer, Window* window, Button* button)
{
    const Bounds BUTTONBOUNDS = geButtonActualBounds(window, button);
    isMouseInBounds(mousePointer, &BUTTONBOUNDS);
}

void drawButton(Framebuffer* framebuffer, Window* window, Button* button)
{
    Point pos = getButtonActualPos(window, button);
    const unsigned int X = pos.x; //The drawn x position of the window
    const unsigned int Y = pos.y; //The drawn y position of the window
    const int WIDTH = button->bounds.dimensions.width; //The drawn width
    const int HEIGHT = button->bounds.dimensions.height; //The drawn height
    
    fillOutlinedCurvedRect(framebuffer, X, Y, WIDTH, HEIGHT, BUTTONBORDERWIDTH, button->fillColour, button->outlineColour, true, true, true, true); //Draw button box

    int TEXTLENGTH = stringLength(button->TEXT);

    const int TEXTOFFSETY = (HEIGHT - (int)getFontCharHeight()) / 2; //Calculate the text offset to center it within the button
    const int TEXTOFFSETX = (WIDTH - ((int)getFontCharWidth()*TEXTLENGTH)) / 2; //Calculate the text offset to center it within the button

    drawString(framebuffer, button->font, button->textColour, button->TEXT, X+TEXTOFFSETX, Y+TEXTOFFSETY); //Draw the title text
}
/**
 * Bassically a constructor cause simpleton Jacob can't live without his OOP 
 * (He might die of a quintuple stroke and double heart-attack if you remove this so please don't)
 */
Button makeButton(char* TEXT, unsigned int relativeX, unsigned int relativeY, int width, int height, unsigned int fillColour, unsigned int outlineColour, unsigned int textColour, PSF1_FONT* font)
{
    Button result;

    result.TEXT=TEXT;
    result.bounds.pos.x = relativeX;
    result.bounds.pos.y = relativeY;
    result.bounds.dimensions.width = width;
    result.bounds.dimensions.height = height;
    result.fillColour = fillColour;
    result.outlineColour = outlineColour;
    result.textColour = textColour;
    result.font = font;

    result.isHightlighted = false;
    result.isPressed = false;

    return result;
}
