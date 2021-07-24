#pragma once
#include "kernel.h"


void kernelInit(BootInfo* boot_info);
void kernelInit_memory(BootInfo* bootInfo);
void kernelInit_gdt(BootInfo *bootInfo);

