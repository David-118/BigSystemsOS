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



#include "bounds.h"

#include "stdbool.h"
#include "guistructures.h"

unsigned int getX1(Bounds* b)
{
    return b->pos.x;
}

unsigned int getY1(Bounds* b)
{
    return b->pos.y;
}

unsigned int getX2(Bounds* b)
{
    return b->pos.x+b->dimensions.width-1;
}

unsigned int getY2(Bounds* b)
{
    return b->pos.y+b->dimensions.height-1;
}

unsigned int getWidth(Bounds* b)
{
    return b->dimensions.width;
}

unsigned int getHeight(Bounds* b)
{
    return b->dimensions.height;
}

void moveBound(Bounds* b, unsigned int x, unsigned int y)
{
    b->pos.x += x;
    b->pos.y += y;
}

bool isPointInBounds(Point* p, Bounds* bounds)
{
    return (p->x >= getX1(bounds)) && (p->x <= getX2(bounds)) && (p->y >= getY1(bounds)) && (p->y <= getY2(bounds));
}

Point getPosRelativeTo(Point* p1, Point* p2)
{
    Point result;

    result.x = p1->x + p2->x;
    result.y = p1->y + p2->y;

    return result;
}

Bounds getBoundsRelativeTo(Bounds* bounds, Point* p)
{
    Bounds result;

    result.pos = getPosRelativeTo(&(bounds->pos), p); //translate the position
    //Assign width and height
    result.dimensions.width = bounds->dimensions.width;
    result.dimensions.height = bounds->dimensions.height;

    return result;
}