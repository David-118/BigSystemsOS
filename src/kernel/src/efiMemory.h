#pragma  once

enum DescType {
    EfiLoaderCode ,
    EfiReservedMemoryType ,
    EfiLoaderData ,
    EfiBootServicesCode ,
    EfiBootServicesData ,
    EfiRuntimeServicesCode ,
    EfiRuntimeServicesData ,
    EfiConventionalMemory ,
    EfiUnusableMemory ,
    EfiACPIReclaimMemory ,
    EfiACPIMemoryNVS ,
    EfiMemoryMappedIO ,
    EfiPalCode ,
};

typedef struct {
    enum DescType type;
    void* physAddr;
    void* virtAddr;
    unsigned long numPages;
    unsigned long attribs;
} EFI_MEMORY_DESCRIPTOR;




extern const char* EFI_MEMORY_TYPE_STRINGS[];