#include "paging.h"
#include <stdint.h>


void paging_setFlag(PageDirEntry* PDE, enum PT_Flag flag, bool enabled) 
{
    uint64_t bitSelector = (uint64_t)1 << flag;
    *PDE =  (*PDE &~bitSelector) | (bitSelector & (uint64_t)enabled * 0XFFFFFFFFFFFFFFFF );
}

bool paging_getFlag(PageDirEntry *PDE, enum PT_Flag flag) {
    uint64_t bitSelector = (uint64_t)1 << flag;
    return (*PDE & bitSelector) > 0;
}

uint64_t paging_getAddress(PageDirEntry *PDE) {
    return (*PDE & 0x000ffffffffff000) >> 12;
}

void paging_setAddress(PageDirEntry *PDE, uint64_t address) {
    address &= 0x000000ffffffffff;
    *PDE &= ~0x000ffffffffff000;
    *PDE |= address << 12;

}