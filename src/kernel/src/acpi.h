#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)){
    unsigned char signature[8];
    uint8_t checksum;
    uint8_t OEMId[6];
    uint8_t revision;
    uint32_t rsdtAddress;
    uint32_t length;
    uint64_t XSDTAddress;
    uint8_t extendedChecksum;
    uint8_t reserved[3];
}ACPI_RSDP2;

typedef struct __attribute__((packed)){
    unsigned char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t OEMID[6];
    uint8_t OEMTableID[8];
    uint32_t OEMRevsion;
    uint32_t CretorID;
    uint32_t CreatorRevision;
}ACPI_SDTHeader;

typedef struct  __attribute__((packed)){
    ACPI_SDTHeader header;
    uint64_t reserved;
} ACPI_MCFGHeader;