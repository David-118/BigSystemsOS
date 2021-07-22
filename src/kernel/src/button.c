#include "boot_info.h"
#include "windowManager.h"
#include "stdbool.h"
#include "button.h"

const unsigned int BUTTONBORDERWIDTH = 10; //The border width of the window

void drawButton(Framebuffer* framebuffer, Window* window, Button* button)
{
    unsigned int x = getButtonActualX(window, button); //The drawn x position of the window
    unsigned int y = getButtonActualY(window, button); //The drawn y position of the window
    unsigned int width = button->width; //The drawn width
    unsigned int height = button->height; //The drawn height
    
    
}

unsigned int getButtonActualX(Window* window, Button* button)
{
    return window->x+button->x;
}

unsigned int getButtonActualY(Window* window, Button* button)
{
    return window->y+button->y;
}