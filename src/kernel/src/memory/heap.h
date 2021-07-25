#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct _s{
    size_t length;
    struct _s* next;
    struct _s* previous;
    bool free;
} HeapSegmentHeader;

void heap_heapSegmentHeader_combineForward(HeapSegmentHeader* header);
void heap_heapSegmentHeader_combineBackward(HeapSegmentHeader* header);
HeapSegmentHeader* head_heapSegmentHeader_split(HeapSegmentHeader* header, size_t splitLength);

void heap_init(void* heapAddress, size_t pageCount);
void* malloc(size_t size);
void free(void* address);

void heap_expand(size_t length);