#include "graphics.h"
#include "kernel.h"
#include "memory/heap.h"
#include "paging/pageMapIndexer.h"
#include "efiMemory.h"
#include "paging/pageFrameAllocator.h"
#include "memory.h"
#include "paging/paging.h"
#include "paging/pageTableManager.h"
#include "gdt/gdt.h"
#include "kernelInit.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "panic.h"
#include "io.h"
#include "acpi.h"
#include <stdint.h>


extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

void kerenelInit_acpi(BootInfo* bootInfo) {
    ACPI_SDTHeader* xsdt = (ACPI_SDTHeader*)(bootInfo->rootSystemDescriptorPointer->XSDTAddress);

    for (int i = 0; i < 4; i++) {
        drawChar(bootInfo->framebuffer, bootInfo->psf1_font, 0x000000ff, xsdt->signature[i], i*8, 16);
    }

}


void kernelInit(BootInfo* bootInfo) {
    kernelInit_gdt();
    kernelInit_memory(bootInfo);
    heap_init((void*)0x0000100000000000, 0x10);
    panic_init(bootInfo);
    kerenelInit_acpi(bootInfo);
    kernelInit_initInterupts();
}

void kernelInit_gdt() {
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.size = sizeof(GDT) - 1; //becuase thats how they defined it
    gdtDescriptor.offset = (uint64_t) &DefaultGDT;
    LoadGDT(&gdtDescriptor);
}

IDTR idtr;
void kernelInit_initInterupts() {
    idtr.limit = 0x0FFF;
    idtr.offset = (uint64_t)pageFrameAllocator_requestPage();

    IDTDescEntry* int_DoubleFault = (IDTDescEntry*)(idtr.offset + 0x8 * sizeof(IDTDescEntry));
    IDTR_IDTDescEntry_setOffset(int_DoubleFault, (uint64_t)doubleFault_handler);
    int_DoubleFault->typeAttr = ITA_TA_InterruptGate;
    int_DoubleFault->selector = 0x08;

    IDTDescEntry* int_GPFault = (IDTDescEntry*)(idtr.offset + 0xD * sizeof(IDTDescEntry));
    IDTR_IDTDescEntry_setOffset(int_GPFault, (uint64_t)gpFault_handler);
    int_GPFault->typeAttr = ITA_TA_InterruptGate;
    int_GPFault->selector = 0x08;

    IDTDescEntry* int_PageFault = (IDTDescEntry*)(idtr.offset + 0xE * sizeof(IDTDescEntry));
    IDTR_IDTDescEntry_setOffset(int_PageFault, (uint64_t)pageFault_handler);
    int_PageFault->typeAttr = ITA_TA_InterruptGate;
    int_PageFault->selector = 0x08;

    IDTDescEntry* int_Keyboard = (IDTDescEntry*)(idtr.offset + 0x21 * sizeof(IDTDescEntry));
    IDTR_IDTDescEntry_setOffset(int_Keyboard, (uint64_t)keyboard_handler);
    int_Keyboard->typeAttr = ITA_TA_InterruptGate;
    int_Keyboard->selector = 0x08;
    
    asm("lidt %0" :: "m"(idtr));

    interrupts_remapPIC();
    kernelInit_io();
}   

void kernelInit_memory(BootInfo* bootInfo) {
    pageFrameAllocator_readEfiMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages  = kernelSize / 4096 + 1;
    
    pageFrameAllocator_lockPages((void*)&_KernelStart, kernelPages);


    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;    
    
    PageTable* pageMapL4 = (PageTable*)pageFrameAllocator_requestPage();
    pageTableManager_init(pageMapL4);


    PageMapIndex pageIndex = PageMapIndexer__virtualAddress(4096 * 52 + 0x50000 * 7);


    memory_memset(pageMapL4, 0 , 4096);

    for (uint64_t i = 0; i < memory_getSize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); i+=4096) {
        pageTableManager_mapMemory((void*)i, (void*)i);
    }
    
    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 4096;
    pageFrameAllocator_lockPages((void*) fbBase, fbSize / 4096 + 1);

    for (uint64_t i = fbBase; i < fbBase + fbSize; i += 4096) {
         pageTableManager_mapMemory((void*)i, (void*)i);
    }


    // Places the page table pointer in a special regester using assembly
    asm("mov %0, %%cr3" :: "r" (pageMapL4));
}

void kernelInit_io() {
    // Setsup maskable interupts
    io_writeToBus(PIC1_DATA, 0b11111101);
    io_writeToBus(PIC2_DATA, 0b11111111);

    // Enables maskable intrupts
    asm("sti");
}