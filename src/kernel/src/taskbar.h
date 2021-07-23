#pragma once

#include "boot_info.h"
#include "windowManager.h"
#include "guistructures.h"
#include "graphics.h"

void drawTaskbar(Framebuffer* framebuffer, TaskBar* taskbar);
TaskBar makeTaskbar(Framebuffer* framebuffer, unsigned int width, unsigned int height, unsigned int colour);