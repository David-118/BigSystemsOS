#pragma once
#include <bits/types.h>
#include <stdint.h>

typedef struct {
    uint64_t PDP_i;
    uint64_t PD_i;
    uint64_t PT_i;
    uint64_t P_i;
} PageMapIndex;


PageMapIndex PageMapIndexer__virtualAddress(uint64_t vAddress);

