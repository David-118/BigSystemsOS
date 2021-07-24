#include "paging/pageMapIndexer.h"
#include "efiMemory.h"
#include "paging/pageFrameAllocator.h"
#include "memory.h"
#include "paging/paging.h"
#include "paging/pageTableManager.h"
#include "gdt/gdt.h"
#include "kernelInit.h"
#include <stdint.h>


extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

void kernelInit(BootInfo* bootInfo) {
    kernelInit_memory(bootInfo);
}

void kernelInit_gdt(BootInfo *bootInfo) {
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.size = sizeof(GDT) - 1; //becuase thats how they defined it
    gdtDescriptor.offset = (uint64_t) &DefaultGDT;
    LoadGDT(&gdtDescriptor);

}

void kernelInit_memory(BootInfo* bootInfo) {
    pageFrameAllocator_readEfiMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages  = kernelSize / 4096 + 1;
    
    pageFrameAllocator_lockPages((void*)&_KernelStart, kernelPages);


    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;    
    
    PageTable* PML4 = (PageTable*)pageFrameAllocator_requestPage();


    PageMapIndex pageIndex = PageMapIndexer__virtualAddress(4096 * 52 + 0x50000 * 7);
    

    memory_memset(PML4, 0 , 4096);

    for (uint64_t i = 0; i < memory_getSize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); i+=4096) {
        pageTableManager_mapMemory(PML4, (void*)i, (void*)i);
    }
    
    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 4096;
    pageFrameAllocator_lockPages((void*) fbBase, fbSize / 4096 + 1);

    for (uint64_t i = fbBase; i < fbBase + fbSize; i += 4096) {
         pageTableManager_mapMemory(PML4, (void*)i, (void*)i);
    }


    // Places the page table pointer in a special regester using assembly
    asm("mov %0, %%cr3" :: "r" (PML4));
}
