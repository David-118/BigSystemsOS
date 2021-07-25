#include <stdint.h>

#include "pageTableManager.h"
#include "pageMapIndexer.h"
#include "pageFrameAllocator.h"
#include "../memory.h"
#include "paging.h"

 PageTable* PLM4;
void pageTableManager_init(PageTable* PML4Address) {
   PLM4 = PML4Address;
}


void pageTableManager_mapMemory(void* virtualMemory, void* physicalMemory) {
    PageMapIndex index = PageMapIndexer__virtualAddress((uint64_t)virtualMemory);
    PageDirEntry PDE;

    PDE = PLM4->entries[index.PDP_i];

    PageTable* PDP;
    if (!paging_getFlag(&PDE, present)) 
    {
        PDP = (PageTable*)pageFrameAllocator_requestPage();
        memory_memset(PDP, 0, 4096);
        paging_setAddress(&PDE, (uint64_t)PDP >> 12);
        paging_setFlag(&PDE, present, true);
        paging_setFlag(&PDE, readWrite, true);
        PLM4->entries[index.PDP_i] = PDE;
    }
    else 
    {
        PDP = (PageTable*)((uint64_t)paging_getAddress(&PDE) << 12);
    }

    PDE = PDP->entries[index.PD_i];

    PageTable* PD;
    if (!paging_getFlag(&PDE, present)) 
    {
        PD = (PageTable*)pageFrameAllocator_requestPage();
        memory_memset(PD, 0, 4096);
        paging_setAddress(&PDE, (uint64_t)PD >> 12);
        paging_setFlag(&PDE, present, true);
        paging_setFlag(&PDE, readWrite, true);
        PDP->entries[index.PD_i] = PDE;
    }
    else 
    {
        PD = (PageTable*)((uint64_t)paging_getAddress(&PDE) << 12);
    }

    PDE = PD->entries[index.PT_i];
    PageTable* PT;
    if (!paging_getFlag(&PDE, present)) 
    {
        PT = (PageTable*)pageFrameAllocator_requestPage();
        memory_memset(PT, 0, 4096);
        paging_setAddress(&PDE, (uint64_t)PT >> 12);
        paging_setFlag(&PDE, present, true);
        paging_setFlag(&PDE, readWrite, true);
        PD->entries[index.PT_i] = PDE;
    }
    else 
    {
        PT = (PageTable*)((uint64_t)paging_getAddress(&PDE) << 12);
    }

    
    PDE = PT->entries[index.P_i];
    paging_setAddress(&PDE, (uint64_t)physicalMemory >> 12);
    paging_setFlag(&PDE, present, true);
    paging_setFlag(&PDE, readWrite, true);
    PT->entries[index.P_i] = PDE;
}




