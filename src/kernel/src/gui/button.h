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
#include "windowManager.h"
#include "../kernel.h"
#include "guistructures.h"
#include "mousePointer.h"
#include "windowManager.h"

void drawButton(Framebuffer* framebuffer, Window* window, Button* button);
Button makeButton(char* TEXT, unsigned int relativeX, unsigned int relativeY, int width, int height, unsigned int fillColour, unsigned int outlineColour, unsigned int textColour, PSF1_FONT* font);
Point getButtonActualPos(Window* window, Button* button);
