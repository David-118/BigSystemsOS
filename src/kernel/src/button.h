#include "stdbool.h"

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

    char* TEXT[64]; //The text in the button

}Button;