#include "IDT.h"
#include <stdint.h>


void IDTR_IDTDescEntry_setOffset(IDTDescEntry *idtDescEntry, uint64_t offset)
{
    idtDescEntry->offset0 = (uint16_t)((offset & 0x000000000000FFFF));
    idtDescEntry->offset1 = (uint16_t)((offset & 0x00000000FFFF0000) >> 16);
    idtDescEntry->offset2 = (uint32_t)((offset & 0xFFFFFFFF00000000) >> 32);
}

uint64_t IDTR_IDTDescEntry_getOffset(IDTDescEntry *idtDescEntry)
{
    uint64_t offset = 0;
    offset |= (uint64_t)idtDescEntry->offset0;
    offset |= (uint64_t)idtDescEntry->offset1 << 16;
    offset |= (uint64_t)idtDescEntry->offset2 << 32;
    return offset;
}