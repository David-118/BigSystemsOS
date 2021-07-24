[bits 64]
LoadGDT:
    lgdt [rdi]
    ;set data regesters to kernel data
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    pop rdi
    mov rax, 0x08
    push rax
    push rdi

    retfq ;return
GLOBAL LoadGDT
