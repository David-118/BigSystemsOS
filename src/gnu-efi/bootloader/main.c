#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
} Framebuffer;

Framebuffer framebuffer;

Framebuffer* initGOP() {
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop);
	if(EFI_ERROR(status)) {
		Print(L"[FAIL] Unable to locate GOP protocol\n\r");
		return NULL;
	} else {
		Print(L"[ OK ] Located GOP\n\r");
	}



	framebuffer.BaseAddress = (void*)gop->Mode->FrameBufferBase;
	framebuffer.BufferSize = gop->Mode->FrameBufferSize;
	framebuffer.Width = gop->Mode->Info->HorizontalResolution;
	framebuffer.Height = gop->Mode->Info->VerticalResolution;
	framebuffer.PixelsPerScanLine = gop->Mode->Info->HorizontalResolution;

	return &framebuffer;
}


EFI_FILE* LoadFile(EFI_FILE* Dir, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* LoadedFile;
	
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Dir == NULL) {
		FileSystem->OpenVolume(FileSystem, &Dir);
	}

	EFI_STATUS s = Dir->Open(Dir, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);

	if (s!=EFI_SUCCESS) {
		return NULL;
	}

	return LoadedFile;
}

int memcmp(const void* aptr, const void* bptr, size_t n) {
	const unsigned char* a = aptr, *b=bptr;
	for (size_t i = 0; i < n; i++) {
		if (a[i] < b[i]) {return -1;}
		else if (a[i] > b[i]) {return 1;}
	}
	return 0;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

	InitializeLib(ImageHandle, SystemTable);
	Print(L"Hello World!!!!\n\r");

	EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable);
	if (Kernel == NULL){
		Print(L"[FAIL]] Kernel not Found\n\r");
	} else {
		Print(L"[ OK ] Kernel Found\n\r");
	}

	Elf64_Ehdr header;
	{
		UINTN FileInfoSize;
		EFI_FILE_INFO* FileInfo;
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header);
		Kernel->Read(Kernel, &size, &header);
	}

	if (
		memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
		header.e_ident[EI_CLASS] != ELFCLASS64 ||
		header.e_ident[EI_DATA] != ELFDATA2LSB ||
		header.e_ident[EI_DATA] != ELFDATA2LSB ||
		header.e_type  != ET_DYN ||
		header.e_machine != EM_X86_64 ||
		header.e_version != EV_CURRENT
	)
	{
		Print(L"[FAIL] Kernel format is bad\r\n");
	}
	else
	{
		Print(L"[ OK ] Kernel Header successfully verified\r\n");
	}
	

	Elf64_Phdr* phdrs;
	{
		Kernel->SetPosition(Kernel, header.e_phoff);
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
		Kernel->Read(Kernel, &size, phdrs);
	}

	for(
		Elf64_Phdr* phdr = phdrs;
		(char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize;
		phdr = (Elf64_Phdr*)(char*)phdr + header.e_phentsize
	)
	{
		switch (phdr->p_type) {
			case PT_LOAD:
			{
				int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
				Elf64_Addr segment = phdr->p_paddr;
				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				Kernel->SetPosition(Kernel, phdr->p_offset);
				UINTN size = phdr->p_filesz;
				Kernel->Read(Kernel, &size, (void*)segment);

				break;
			}
		}
	}

	Print(L"[ OK ] Kernel Loaded\n\r");

	Framebuffer* newBuffer = initGOP();
	
	Print(L"Base: 0x%x\n\rSize: 0x%x \n\rWidth: %d\n\rHeight: %d\n\rPixelsPerScanLine: %d\n\r\n\r", 
	newBuffer->BaseAddress, 
	newBuffer->BufferSize, 
	newBuffer->Width, 
	newBuffer->Height, 
	newBuffer->PixelsPerScanLine);

	unsigned int y = 50;
	unsigned int BBP = 4;

	for (unsigned int x = 0; x < newBuffer->Width / 2 * BBP; x++) {
		*(unsigned int*)(x + (y * newBuffer->PixelsPerScanLine * BBP) + newBuffer->BaseAddress) = 0xffffffff;
	}

	//int (*KernelStart)() = ((__attribute__((sysv_abi)) int (*)() ) header.e_entry);

	//Print(L"%d\r\n", KernelStart());

	return EFI_SUCCESS; // Exit the UEFI application
}
