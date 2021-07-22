
#include "button.h"

const unsigned int BUTTONBORDERWIDTH = 2; //The border width of the window


unsigned int getButtonActualX(Window* window, Button* button)
{
    return getWindowX(window)+button->relativeX;
}

unsigned int getButtonActualY(Window* window, Button* button)
{
    return getWindowY(window)+button->relativeY;
}

void drawButton(Framebuffer* framebuffer, Window* window, Button* button)
{
    unsigned int x = getButtonActualX(window, button); //The drawn x position of the window
    unsigned int y = getButtonActualY(window, button); //The drawn y position of the window
    unsigned int width = button->width; //The drawn width
    unsigned int height = button->height; //The drawn height
    
    fillOutlinedRect(framebuffer, x, y, width, height, BUTTONBORDERWIDTH, button->fillColour, button->outlineColour);

    drawString(framebuffer, button->font, button->textColour, button->TEXT, x, y); //Draw the title text
}
/**
 * Bassically a constructor cause simpleton Jacob can't live without his OOP 
 * (He might die of a quintuple stroke and double heart-attack if you remove this so please don't)
 */
Button makeButton(char* TEXT, unsigned int relativeX, unsigned int relativeY, int width, int height, unsigned int fillColour, unsigned int outlineColour, unsigned int textColour, PSF1_FONT* font)
{
    Button result;

    result.TEXT=TEXT;
    result.relativeX = relativeX;
    result.relativeY = relativeY;
    result.width = width;
    result.height = height;
    result.fillColour = fillColour;
    result.outlineColour = outlineColour;
    result.textColour = textColour;
    result.font = font;

    result.isHightlighted = false;
    result.isPressed = false;

    return result;
}
