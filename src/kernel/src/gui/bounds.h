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

#include "guistructures.h"
#include "stdbool.h"

unsigned int getX1(Bounds* b);
unsigned int getY1(Bounds* b);
unsigned int getX2(Bounds* b);
unsigned int getY2(Bounds* b);

unsigned int getWidth(Bounds* b);
unsigned int getHeight(Bounds* b);

void moveBound(Bounds* b, unsigned int x, unsigned int y);

bool isPointInBounds(Point* p, Bounds* bounds);

Point getPosRelativeTo(Point* p1, Point* p2);
Bounds getBoundsRelativeTo(Bounds* bounds, Point* p);