#pragma once
#include "boot_info.h"
#include "stdbool.h"
/**
 * A Button
 */
typedef struct
{
	unsigned int relativeX; //The x position relative to the origin of the parent component (e.g trueX = relativeX + myParentX)
    unsigned int relativeY; //The y position relative to the origin of the parent component (e.g trueY = relativeY + myParentY)
	unsigned int width; //The width of the button
    unsigned int height; //The height of the button

    bool isHightlighted; //Is the button highlighted (by the mouse hovering over it)
    bool isPressed; //Is the button being pressed

    unsigned int fillColour; //The filled in colour of the window
    unsigned int outlineColour; //The outlined colour of the window
    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    char* TEXT; //The text in the button

    

}Button;

/**
 * A Window
 */
typedef struct
{
	unsigned int x; //The x position of the window (note this includes the borders (if they exist))
    unsigned int y; //The y position of the window (note this includes the borders (if they exist))
	unsigned int width; //The width of the window (note this includes the borders (if they exist))
    unsigned int height; //The height of the window (note this includes the borders (if they exist))
    bool isFullScreen; //Overrides the standard height and width specified so when "un maximised" it goes back to its original size

    bool isMinimised; //Stores if the window is minismised

    char* NAME; //The name of the window

    bool isResizable; //Is the window resizeable
    bool hasBorders; //Does the window have borders

    unsigned int borderColour; //The border colour of a window

    unsigned int textColour; //The colour of the text
    PSF1_FONT* font; //The font

    Button buttons[3]; //The buttons for the window

}Window;