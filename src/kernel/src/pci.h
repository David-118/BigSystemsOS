#pragma once
#include <stdint.h>
#include "acpi.h"

typedef struct {
    uint16_t vendorID;
    uint16_t deviceID;
    uint16_t command;
    uint16_t status;
    uint8_t revisionID;
    uint8_t progIF;
    uint8_t subclass;
    uint8_t class;
    uint8_t cachelinesize;
    uint8_t latencyTimer;
    uint8_t BSIT;
} pci_DeviceHeader;

void pci_enumeratePCI(ACPI_MCFGHeader* mcfg);
