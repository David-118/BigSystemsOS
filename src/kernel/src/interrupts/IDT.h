#pragma once
#include <stdint.h>

#define ITA_TA_InterruptGate 0b10001110
#define ITA_TA_CallGate      0b10001100
#define ITA_TA_TrapGate      0b10001111


typedef struct {
    uint16_t offset0;
    uint16_t selector;
    uint8_t ist;
    uint8_t typeAttr;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t extra;
} IDTDescEntry;

void IDTR_IDTDescEntry_setOffset(IDTDescEntry* idtDescEntry, uint64_t offset);
uint64_t IDTR_IDTDescEntry_getOffset(IDTDescEntry* idtDescEntry);

typedef struct __attribute__((packed)){
    uint16_t limit;
    uint64_t offset;
} IDTR;