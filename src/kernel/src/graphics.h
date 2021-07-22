#pragma once

#include "boot_info.h"
#include "windowManager.h"
#include "guistructures.h"

void clearScreen(Framebuffer* framebuffer, unsigned int colour);

void drawChar(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void drawString(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff);

unsigned int getFontCharWidth();
unsigned int getFontCharHeight();


void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour);

void fillRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour);
void fillGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colourTop, unsigned int colourBottom);

void fillCircle(Framebuffer* framebuffer, int centerX, int centerY, int startX, int startY, int endX, int endY, int radius, unsigned int colour);

void fillOutlinedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour);
void fillOutlinedGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColourTop, unsigned int fillColourBottom, unsigned int outlineColourTop, unsigned int outlineColourBottom);

void fillOutlinedCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight);
void fillOutlinedGradientCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColourTop, unsigned int fillColourBottom, unsigned int outlineColourTop, unsigned int outlineColourBottom, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight);

void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour);
void outlineGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colourTop, unsigned int colourBottom);

void outlineCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight);
void outlineGradientCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colourTop, unsigned int colourBottom, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight);

void drawline(Framebuffer* framebuffer, int x0, int y0, int x1, int y1, unsigned int colour);

unsigned int changeBrightness(unsigned int colour, int brightness);

unsigned int makeColour(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

unsigned int getColourGradient(unsigned int colourTop, unsigned int colourBottom, unsigned int pos, unsigned int size);

unsigned int getAlpha(unsigned int colour);
unsigned int getRed(unsigned int colour);
unsigned int getGreen(unsigned int colour);
unsigned int getBlue(unsigned int colour);