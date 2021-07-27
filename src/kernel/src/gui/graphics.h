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
#include "windowManager.h"
#include "guistructures.h"

void clearScreen(Framebuffer* framebuffer, unsigned int colour);

void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour);
unsigned int getPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y);

void drawChar(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void drawString(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff);

unsigned int getFontCharWidth();
unsigned int getFontCharHeight();

void drawImageToBuffer(Framebuffer* framebuffer, Framebuffer* image, unsigned int x, unsigned int y);

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

unsigned int makeColour(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

unsigned int getColourGradient(unsigned int colourTop, unsigned int colourBottom, unsigned int pos, unsigned int size);

unsigned int changeBrightness(unsigned int colour, int brightness);

unsigned int getAlpha(unsigned int colour);
unsigned int getRed(unsigned int colour);
unsigned int getGreen(unsigned int colour);
unsigned int getBlue(unsigned int colour);