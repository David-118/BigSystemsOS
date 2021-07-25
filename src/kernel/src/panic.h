#pragma once

#include "graphics.h"
#include "kernel.h"

void panic_init(BootInfo *bootInfo);
void panic_panic(const char* message);
void panic_test();