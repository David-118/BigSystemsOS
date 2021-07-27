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
#include "boot_info.h"
#include "stdbool.h"


typedef struct
{
	unsigned int x; //The x position
    unsigned int y; //The y position
}Point;

typedef struct
{
	unsigned int width; //The width
    unsigned int height; //The height
}Dimensions;

typedef struct
{
	Point pos; //The actual position fo the object
    Dimensions dimensions; //The size
}Bounds;

/**
 * A Button
 */
typedef struct
{

    Bounds bounds; //The x,y position relative to the origin of the parent component (e.g trueX = relativeX + myParentX), also the width and height of the button

    bool isHightlighted; //Is the button highlighted (by the mouse hovering over it)
    bool isPressed; //Is the button being pressed

    bool isFocused; //True if the object is in focus from the user

    unsigned int fillColour; //The filled in colour of the window
    unsigned int outlineColour; //The outlined colour of the window
    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    char* TEXT; //The text in the button

}Button;

typedef struct
{

    Bounds bounds; //The x,y position relative to the origin of the parent component (e.g trueX = relativeX + myParentX), also the width and height of the button

    bool isEditable; //Is the button highlighted (by the mouse hovering over it)
    bool isFocused; //True if the object is in focus from the user

    unsigned int fillColour; //The filled in colour of the window
    unsigned int outlineColour; //The outlined colour of the window
    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    char* TEXT; //The text in the field

    

}TextField;

/**
 * A Window
 */
typedef struct
{

    Bounds bounds; //The x,y position + width,height of the window (note this includes the borders (if they exist))

    bool isFullScreen; //Overrides the standard height and width specified so when "un maximised" it goes back to its original size

    bool isMinimised; //Stores if the window is minismised

    bool isFocused; //True if the object is in focus from the user

    char* NAME; //The name of the window

    bool isResizable; //Is the window resizeable
    bool hasBorders; //Does the window have borders

    unsigned int borderColour; //The border colour of a window

    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    Button buttons[3]; //The buttons for the window

}Window;

typedef struct
{

    Bounds bounds; //The x,y position + width,height of the canvas (note this may be smaller than a window if that window has borders)

    Button buttons[64]; //The buttons for the for the canvas

    Framebuffer* canvasbuffer; //The buffer to draw

}Canvas;

typedef struct
{
    Bounds bounds; //The x,y position + width,height of the taskbar (note this includes the borders (if they exist))

    unsigned int colour; //The colour of the taskbarbox

    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    Button buttons[64]; //The buttons for the for the taskbar

}TaskBar;

typedef struct
{
	//Add stuff to this

}Desktop;

typedef struct
{
	Point pos;

    Framebuffer* mouseImage; //The buffer to draw
}MousePointer;

