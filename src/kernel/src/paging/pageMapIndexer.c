#include "pageMapIndexer.h"

PageMapIndex PageMapIndexer__virtualAddress(uint64_t vAddress) {
    PageMapIndex this;
    vAddress >>= 12;
    this.P_i = vAddress & 0x1ff;
    
    vAddress >>= 9;
    this.PT_i = vAddress & 0x1ff;

    vAddress >>= 9;
    this.PD_i = vAddress & 0x1ff;

    vAddress >>= 9;
    this.PDP_i = vAddress & 0x1ff;
    
    return this;
}