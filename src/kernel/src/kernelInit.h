#pragma once
#include "kernel.h"


void kernelInit(BootInfo* boot_info);
void kernelInit_memory();
void kernelInit_gdt();
void kernelInit_initInterupts();
void kernelInit_io();
