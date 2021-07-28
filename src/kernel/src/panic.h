#pragma once

#include "graphics.h"
#include "kernel.h"

void panic_init(BootInfo *bootInfo);
void panic_panic(const char* message);
void panic_debug(const char* message);
void panic_debug_char(const char chr);
void panic_test();