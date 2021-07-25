#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
    size_t length;
    struct HeapSegmentHeader* next;
    struct HeapSegmentHeader* last;
    bool free;
} HeapSegmentHeader;

void heap_heapSegmentHeader_combineForward(HeapSegmentHeader* header);
void heap_heapSegmentHeader_combineBackward(HeapSegmentHeader* header);
HeapSegmentHeader* split(size_t splitLength);

void heap_init(void* heapAddress, size_t pageCount);
void* malloc(size_t size);
void free(void* address);

void expand_head(void* length);