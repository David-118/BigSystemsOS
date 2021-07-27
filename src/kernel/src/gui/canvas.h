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
#include "guistructures.h"
#include "bounds.h"
#include "windowManager.h"

void drawCanvas(Framebuffer* framebuffer, Canvas* canvas, Window* window);

unsigned int getCanvasActualX(Window* window, Canvas* canvas);
unsigned int getCanvasActualY(Window* window, Canvas* canvas);