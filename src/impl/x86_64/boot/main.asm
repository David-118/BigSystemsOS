global start
extern long_mode_start

section .text
;set the mode to 32-bit as instructions are still in 32 bit mode
bits 32
start:
    ;store address of stack_top in esp regester
    mov esp, stack_top

    ;checks cpu meets requirments and os has loaded
    call check_multiboot
    call check_cpuid
    call check_long_mode

    ;sets up memory paging
    call setup_page_tables
    call enable_paging

    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

    hlt

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret
; throw error
.no_multiboot:
    mov al, "M"
    jmp error



check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    jp .no_cpuid
; throw error
.no_cpuid:
    mov al, "C"
    jmp error


check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode
    mov eax, 0x80000001
    
    cpuid
    test edx, 1 << 29
    jb .no_long_mode

    ret
;throw error
.no_long_mode:
    mov al, "L"
    jmp error


setup_page_tables:
    mov eax, page_table_l3
    or eax, 0b11 ; present and writable flags
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b11 ; present and writable flags
    mov [page_table_l3], eax

    mov ecx, 0 ; counter

.loop:
    mov eax, 0x200000 ; 2MiB
    mul ecx
    or eax, 0b10000011
    mov [page_table_l2 + eax * 8]

    inc ecx ; counter++
    cmp ecx, 512 ; check if whole table is mapped
    jne .loop ; if not countinue

    ret

enable_paging:
    ; pass page table location to cpu
    mov eax, page_table_l4
    mov cr3, eax

    ; enable physical address location (somthing to do with 64 bit paging)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ;enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret



error:
	; print "ERR: X" where X is the error code
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt

section .bss
align 4096

page_table_l4:
    resb 4096

page_table_l3:
    resb 4096

page_table_l2:
    resb 4096

stack_bottom:
    ;reserve 16kB of memoroy
    resb 4096 * 4
stack_top:

section .rodata
; 64 bit global descriptor table
gdt64:
    dq 0; Zero Entry
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 53); code segment

.pointer:
    dw $ - gdt64 - 1
    dq gdt64



