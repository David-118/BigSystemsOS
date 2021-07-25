#pragma once
#include "paging.h"

void pageTableManager_init(PageTable* PML4Address);
void pageTableManager_mapMemory(void* virtualMemory, void* physicalMemory);





