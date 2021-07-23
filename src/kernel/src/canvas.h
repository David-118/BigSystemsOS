#pragma once
#include "boot_info.h"
#include "stdbool.h"
#include "guistructures.h"

void drawCanvas(Framebuffer* framebuffer, Canvas* canvas, Window* window);

unsigned int getCanvasActualX(Window* window, Canvas* canvas);
unsigned int getCanvasActualY(Window* window, Canvas* canvas);