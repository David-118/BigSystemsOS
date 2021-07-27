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
#include "../kernel.h"
#include "button.h"
#include "stdbool.h"
#include "guistructures.h"


void drawWindow(Framebuffer* framebuffer, Window* window);
Window makeWindow(Framebuffer* framebuffer, char* NAME, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders, unsigned int textColour, PSF1_FONT* font, unsigned int borderColour);
void resizeWindow(Framebuffer* framebuffer, Window* window, unsigned int width, unsigned int height);
void moveWindow(Window* window, unsigned int x, unsigned int y);
void setFullScreen(Framebuffer* framebuffer, Window* window, bool isFullScreen);
void setMinimised(Window* window, bool isMinimised);

Point getWindowPos(Window* window);
Dimensions getWindowDimensions(Framebuffer* framebuffer, Window* window);
Bounds getWindowBounds(Framebuffer* framebuffer, Window* window);

void updateTitleBarButtonPosition(Framebuffer* framebuffer, Window* window);

