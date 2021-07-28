#include "pci.h"
#include "acpi.h"
#include <stdint.h>
#include "paging/pageTableManager.h"
#include "panic.h"
#include "kernel.h"

void pci_enumerateFunction(uint64_t deviceAddress, uint64_t function) {
    uint64_t functionOffset = function << 12;
    uint64_t functionAddress = deviceAddress + functionOffset;
    pageTableManager_mapMemory((void*)functionAddress, (void*)functionAddress);

    pci_DeviceHeader* deviceHeader = (pci_DeviceHeader*)functionAddress;
    
    if (deviceHeader->deviceID == 0 || 
        deviceHeader->deviceID == 0xffff) {
            return; //device not valid
    } 

    panic_debug(uint_to_string(function));
    panic_debug(uint_to_hex(deviceHeader->vendorID));
    panic_debug(uint_to_hex(deviceHeader->deviceID));
    panic_debug("");
}
void pci_enumerateDevice(uint64_t busAddress, uint64_t device) {
    uint64_t deviceOffset = device << 15;
    uint64_t devieAddress = busAddress + deviceOffset;
    pageTableManager_mapMemory((void*)devieAddress, (void*)devieAddress);

    pci_DeviceHeader* deviceHeader = (pci_DeviceHeader*)devieAddress;
    
    if (deviceHeader->deviceID == 0 || 
        deviceHeader->deviceID == 0xffff) {
            return; //device not valid
    } 

    for (uint64_t function = 0; function < 8; function++) {
        pci_enumerateFunction(devieAddress, function);
    }
}

void pci_enumerateBus(uint64_t baseAddress, uint64_t bus) {
    uint64_t busOffset = bus << 20;
    uint64_t busAddress = baseAddress + busOffset;
    pageTableManager_mapMemory((void*)busAddress, (void*)busAddress);

    pci_DeviceHeader* deviceHeader = (pci_DeviceHeader*)busAddress;
    
    if (deviceHeader->deviceID == 0 || 
        deviceHeader->deviceID == 0xffff) {
            return; //device not valid
    } 

    for (uint64_t device = 0; device < 32; device++) {
        pci_enumerateDevice(busAddress, device);
    }
}

void pci_enumeratePCI(ACPI_MCFGHeader* mcfg) {
    int deviceConfigCount = ((mcfg->header.length) - sizeof(ACPI_MCFGHeader)) / sizeof(ACPI_DeviceConfig);
    panic_debug(uint_to_string((mcfg->header.length - sizeof(ACPI_MCFGHeader))));

    for (int deviceConfigOffset = 0; deviceConfigOffset < deviceConfigCount; deviceConfigOffset++) {
        ACPI_DeviceConfig* deviceConfig = (ACPI_DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI_MCFGHeader) + (sizeof(ACPI_DeviceConfig) * deviceConfigOffset));

        for (uint64_t bus = deviceConfig->startBus; bus < deviceConfig->endBus; bus++) {
            pci_enumerateBus(deviceConfig->baseAddress, bus);
        }

    }
}
