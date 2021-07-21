PSF1_FONT* LoadPSF1Font(EFI_FILE* Dir, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);

void fail(short unsigned int* message);

void sucess(short unsigned int* message);

Framebuffer* initGOP();

EFI_FILE* LoadFile(EFI_FILE* Dir, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);

int memcmp(const void* aptr, const void* bptr, size_t n);

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);