#include <stdint.h>
#include "acpi.h"
#include "panic.h"

void* ACPI_findTable(ACPI_SDTHeader* sdtHeader, char* signature) 
{
    int entries = (sdtHeader->length - sizeof(ACPI_SDTHeader)) / 8;
    for (int i = 0; i < entries; i++) {
        ACPI_SDTHeader* newSDTHeader = (ACPI_SDTHeader*)*(uint64_t*)((uint64_t)sdtHeader + sizeof(ACPI_SDTHeader) + (i*8));
        for (int j = 0; j < 4; j++) {
            if (newSDTHeader->signature[j] != signature[j]) {
                break;
            }
            if (j == 3) {return newSDTHeader;}
        }
    }
    return NULL;
}