
#pragma once
#include "boot_info.h"
#include "stdbool.h"
#include "windowManager.h"
#include "kernel.h"
#include "guistructures.h"

void drawButton(Framebuffer* framebuffer, Window* window, Button* button);
Button makeButton(char* TEXT, unsigned int relativeX, unsigned int relativeY, int width, int height, unsigned int fillColour, unsigned int outlineColour, unsigned int textColour, PSF1_FONT* font);
unsigned int getButtonActualX(Window* window, Button* button);
unsigned int getButtonActualY(Window* window, Button* button);
