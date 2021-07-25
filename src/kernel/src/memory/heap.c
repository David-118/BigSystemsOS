#include "heap.h"
#include "../paging/pageTableManager.h"
#include "../paging/pageFrameAllocator.h"
#include "../kernelInit.h"
#include <stddef.h>
#include <stdint.h>
#include "../panic.h"

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

void* malloc(size_t size) {
    if (size % 0x10 > 0) {
        size -= (size % 0x10);
        size += 0x10;
    }

    if (size==0) return NULL;

    HeapSegmentHeader* currentSeg = (HeapSegmentHeader*) heapStart;
    while (true) 
    {
        if (currentSeg->free) 
        {
            if (currentSeg->length > size) {
                head_heapSegmentHeader_split(size);
                currentSeg->free = false;
                return (void*)((uint64_t) currentSeg + sizeof(HeapSegmentHeader));
            }
            else if (currentSeg-> length == size)
            {
                currentSeg->free = false;
                return (void*)((uint64_t) currentSeg + sizeof(HeapSegmentHeader)); 
            }
        }
        if (currentSeg->next == NULL) {break;}
        currentSeg = currentSeg->next;
    }

    heap_expand(size);
    return malloc(size);
}

HeapSegmentHeader* head_heapSegmentHeader_split(size_t splitLength) {
    return NULL;
}

void heap_expand(size_t length) {

}