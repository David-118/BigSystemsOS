#pragma once

#include <stdint.h>

typedef struct __attribute__((packed)) { 
    uint16_t size;
    uint64_t offset;
} GDTDescriptor ;

typedef struct __attribute__((packed)){
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t accessBytes;
    uint8_t limit1Flags;
    uint8_t base2;
} GDTEntry;

typedef struct __attribute__((packed, aligned(0x1000)))
{
    GDTEntry null;
    GDTEntry kernelCode;
    GDTEntry kernelData;
    GDTEntry userNull;
    GDTEntry userCode;
    GDTEntry userData;
} GDT;

extern GDT DefaultGDT;
extern void LoadGDT(GDTDescriptor* gdtDescriptor);