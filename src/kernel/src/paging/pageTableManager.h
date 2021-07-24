#pragma once
#include "paging.h"

void pageTableManager_mapMemory(PageTable* PML4Address, void* virtualMemory, void* physicalMemory);




