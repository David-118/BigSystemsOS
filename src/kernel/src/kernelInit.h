#pragma once
#include "kernel.h"


void kernelInit(BootInfo* boot_info);
void kernelInit_memory();
void kernelInit_gdt(BootInfo *bootInfo);
void kernelInit_initInterupts();

