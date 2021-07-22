#pragma once
#include "boot_info.h"
#include "kernel.h"
#include "button.h"
#include "stdbool.h"
#include "guistructures.h"


void drawWindow(Framebuffer* framebuffer, Window* window);
Window makeWindow(Framebuffer* framebuffer, char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour);
void resizeWindow(Framebuffer* framebuffer, Window* window, unsigned int width, unsigned int height);
void moveWindow(Window* window, unsigned int x, unsigned int y);
void setFullScreen(Framebuffer* framebuffer, Window* window, bool isFullScreen);
void setMinimised(Window* window, bool isMinimised);

unsigned int getWindowWidth(Framebuffer* framebuffer, Window* window);
unsigned int getWindowHeight(Framebuffer* framebuffer, Window* window);
unsigned int getWindowX(Window* window);
unsigned int getWindowY(Window* window);

void updateTitleBarButtonPosition(Framebuffer* framebuffer, Window* window);

