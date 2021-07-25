#include "heap.h"
#include "../paging/pageTableManager.h"
#include "../paging/pageFrameAllocator.h"
#include "../kernelInit.h"

void* heapStart;
void* heapEnd;

HeapSegmentHeader* lastHeader;

void heap_init(void *heapAddress, size_t pageCount) 
{
    void* pos = heapAddress;

    for (size_t i = 0; i < pageCount; i++) 
    {
        pageTableManager_mapMemory(pos, pageFrameAllocator_requestPage());
        pos = (void*)((size_t)pos + 0x1000);
    }

    size_t heapLength = pageCount * 0x1000;

    heapStart = heapAddress;
    heapEnd = (void*)((size_t)heapStart + heapLength);
    HeapSegmentHeader* startSeg = (HeapSegmentHeader*)heapAddress;
    startSeg->length = heapLength - sizeof(HeapSegmentHeader);
    startSeg->next = NULL;
    startSeg->last = NULL;
    startSeg->free = true;
    lastHeader = startSeg;
}