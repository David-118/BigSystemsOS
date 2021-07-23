build-x86_64:
	@cd src/gnu-efi/ && make
	@cd src/kernel/ && make setup

	@cd src/gnu-efi/ && make bootloader
	@cd src/kernel/ && make kernel && make buildimg

build-x86_64_f32:
	@cd src/gnu-efi/ && make
	@cd src/kernel/ && make setup

	@cd src/gnu-efi/ && make bootloader
	@cd src/kernel/ && make kernel && make buildimg_32	

clean:
	@cd src/gnu-efi/ && make clean
	@cd src/kernel/ && make clean


run:
	@cd src/kernel && make run